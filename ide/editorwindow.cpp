#include "editorwindow.hpp"
#include "ui_editorwindow.h"

#include <iostream>
#include <algorithm>

#include <QDir>
#include <QFileDialog>

#include <KHelpMenu>
#include <KAboutData>

EditorWindow::EditorWindow(QWidget *parent, QString projectDirectory) : QMainWindow(parent), ui(new Ui::EditorWindow), directory(projectDirectory) {
	ui->setupUi(this);
	setWindowTitle("BRUX IDE");
	QMenu* newMenu = new QMenu("File");
	connect(newMenu->addAction("Open File"), SIGNAL(triggered()) , this, SLOT(openFile()));
	connect(newMenu->addAction("Open Folder"), SIGNAL(triggered()) , this, SLOT(openDirectory()));
	connect(newMenu->addAction("Test Project"), SIGNAL(triggered()) , this, SLOT(testProject()));
	KHelpMenu* Help = new KHelpMenu(this, KAboutData::applicationData());
	ui->menubar->addMenu(newMenu);
	ui->menubar->addMenu(Help->menu());

	directoryView.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

	QTreeView* treeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	connect(ui->centralwidget->findChild<QTabWidget*>("fileTabs"), &QTabWidget::tabCloseRequested, this, &EditorWindow::closeFile);
	connect(treeView, &QTreeView::doubleClicked, this, &EditorWindow::handleDoubleClick);

	textEditorInstance = KTextEditor::Editor::instance();
}

EditorWindow::~EditorWindow() {
	int remainingFiles = documentList.size();

	openTextFiles.clear();

	while (remainingFiles != 0) {
		closeFile(0);
		remainingFiles--;
	}

	delete ui;
}

void EditorWindow::handleDoubleClick(QModelIndex index) {
	// Always get column 0 (name)
	index = index.siblingAtColumn(0);

	QTreeView* treeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	QString item = treeView->model()->data(index).toString();

	processFile(directoryView.filePath(index), item);
}

void EditorWindow::openDirectory(bool checked) {
	QString newDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), getenv("HOME"), QFileDialog::ShowDirsOnly);

	if (!newDir.isEmpty()) {
		processDirectory(newDir);
	}
}

void EditorWindow::testProject() {
	if (directory == "") return; // No directory open, return.
	char* desktop = getenv("XDG_CURRENT_DESKTOP");
	std::string environment, command;

	if (desktop == NULL) {
		std::cout << "XDG_CURRENT_DESKTOP is unset. Defaulting to no terminal." << std::endl;
		environment = "";
	} else environment = desktop;

	// Determine which command should be used
	if (environment == "KDE") command = "konsole --workdir " + directory.toStdString() + " -e \"brux\" &";
	else if (environment == "XFCE") command = "xfce4-terminal --working-directory " + directory.toStdString() + " --command=\"brux\" &";
	else if (environment.find("GNOME") != environment.npos) command = "gnome-terminal --working-directory " + directory.toStdString() + " --command=\"brux\" &"; // GNOME and GNOME Flashback
	else command = ("cd " + directory + " && brux &").toStdString(); // Default to running in the background with no terminal
	system(command.c_str());
}


void EditorWindow::openFile(bool checked) {
	QString openFile = QFileDialog::getOpenFileName(this, tr("Open File"), getenv("HOME"));

	if (!openFile.isEmpty()) {
		processFile(openFile, openFile.split("/").last());
	}
}

bool EditorWindow::isFile(QString path) {
	QFileInfo fileCheck{path};
	return fileCheck.exists() && fileCheck.isFile();
}

bool EditorWindow::isDirectory(QString path) {
	QFileInfo fileCheck{path};
	return fileCheck.exists() && fileCheck.isDir();
}

bool EditorWindow::isTilemap(QString path) {
	QFile fileCheck{path};
	if (!fileCheck.exists()) return false;

	if (path.endsWith(".tmx")) return true;
	if (!path.endsWith(".json")) return false;

	QString fileContents = fileCheck.readAll();

	if (fileContents.contains("\"tiledversion\"")) return true;
	return false;
}

void EditorWindow::processFile(QString path, QString name, bool newFile) {
	int listSize = documentList.size();
	// New file logic
	if (newFile) {
		documentList.push_back(textEditorInstance->createDocument(this));
		documentViewList.push_back(documentList[listSize]->createView(nullptr));
		createTab("New File", listSize);
		return;
	}

	// Existing file logic
	if (!isFile(path)) return; // No thanks!
	if (isTilemap(path)) {
		return; // Do this later
	}

	if(std::find(openTextFiles.begin(), openTextFiles.end(), path) != openTextFiles.end()) return;

	QDir dirExistsCheck{path};
	if (!dirExistsCheck.exists()) {
		documentList.push_back(textEditorInstance->createDocument(this));
		documentList[listSize]->openUrl(QUrl("file://" + path));
		documentViewList.push_back(documentList[listSize]->createView(nullptr));
		createTab(name, listSize);
		openTextFiles.push_back(path);
	}
}

void EditorWindow::processDirectory(QString path, bool doCloseFiles) {
	if (!isDirectory(path)) return;
	if (doCloseFiles) {
		int remainingFiles = documentList.size();

		openTextFiles.clear();

		while (remainingFiles != 0) {
			closeFile(0);
			remainingFiles--;
		}
	}

	QString shortDir = path.split("/").last();

	setWindowTitle(shortDir + " - BRUX IDE");

	directory = path;
	directoryView.setRootPath(directory);

	QTreeView* treeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	treeView->setModel(&directoryView);
	treeView->setRootIndex(directoryView.index(directory));
	treeView->hideColumn(3);
	int sizeOfColumn = treeView->maximumWidth() / 4;
	treeView->setColumnWidth(0, sizeOfColumn * 2.5f);
	treeView->setColumnWidth(1, sizeOfColumn * 0.75f);
	treeView->setColumnWidth(2, sizeOfColumn * 0.5f);
}

void EditorWindow::closeFile(int index) {
	documentViewList[index]->close();
	documentList[index]->closeStream();
	closeTab(index);
	if (openTextFiles.size() == 0) return; // We manually cleared this so don't erase from openTextFiles.
	openTextFiles.erase(openTextFiles.begin() + index);
}

void EditorWindow::createTab(QString name, int documentIndex) {
	// Create the new tab
	QTabWidget* tabWidget = ui->centralwidget->findChild<QTabWidget*>("fileTabs");
	QWidget* newTab = new QWidget(tabWidget);
	QHBoxLayout* newTabLayout = new QHBoxLayout;
	newTab->setLayout(newTabLayout);
	if (tabWidget->count() != 0) tabWidget->addTab(newTab, name);
	else tabWidget->insertTab(0, newTab, name);

	// Create a new document view for the new tab
	newTabLayout->addWidget(documentViewList[documentIndex]);

	// Finally, change the current index to the newest tab
	tabWidget->setCurrentIndex(tabWidget->count()-1);
}

void EditorWindow::closeTab(int index) {
	QTabWidget* tabWidget = ui->centralwidget->findChild<QTabWidget*>("fileTabs");
	tabWidget->removeTab(index);
}
