#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <iostream>
#include <algorithm>

#include <QDir>
#include <QFileDialog>

#include <KHelpMenu>
#include <KAboutData>

EditorWindow::EditorWindow(QWidget *parent, QString projectDirectory) : QMainWindow(parent), ui(new Ui::EditorWindow), Directory(projectDirectory) {
	ui->setupUi(this);
	setWindowTitle("BRUX IDE");
	QMenu* newMenu = new QMenu("File");
	connect(newMenu->addAction("Open File"), SIGNAL(triggered()) , this, SLOT(openFile()));
	connect(newMenu->addAction("Open Folder"), SIGNAL(triggered()) , this, SLOT(openDirectory()));
	KHelpMenu* Help = new KHelpMenu(this, KAboutData::applicationData());
	ui->menubar->addMenu(newMenu);
	ui->menubar->addMenu(Help->menu());

	DirectoryView.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);

	auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	connect(ui->centralwidget->findChild<QTabWidget*>("fileTabs"), &QTabWidget::tabCloseRequested, this, &EditorWindow::closeFile);
	connect(TreeView, &QTreeView::doubleClicked, this, &EditorWindow::handleDoubleClick);

	TextEditorInstance = KTextEditor::Editor::instance();
}

EditorWindow::~EditorWindow() {
	int remainingFiles = Documents.size();

	OpenSourceFiles.clear();

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

	processFile(DirectoryView.filePath(index), item);
}

void EditorWindow::openDirectory(bool checked) {
	QString newDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), getenv("HOME"), QFileDialog::ShowDirsOnly);

	if (!newDir.isEmpty()) {
		processDirectory(newDir);
	}
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
	int vecSize = Documents.size();
	// New file logic
	if (newFile) {
		Documents.push_back(TextEditorInstance->createDocument(this));
		DocumentViews.push_back(Documents[vecSize]->createView(nullptr));
		createTab("New File", vecSize);
		return;
	}

	// Existing file logic
	if (!isFile(path)) return; // No thanks!
	if (isTilemap(path)) {
		return; // Do this later
	}

	if(std::find(OpenSourceFiles.begin(), OpenSourceFiles.end(), path) != OpenSourceFiles.end()) return;

	QDir dirExistsCheck{path};
	if (!dirExistsCheck.exists()) {
		Documents.push_back(TextEditorInstance->createDocument(this));
		Documents[vecSize]->openUrl(QUrl("file://" + path));
		DocumentViews.push_back(Documents[vecSize]->createView(nullptr));
		createTab(name, vecSize);
		OpenSourceFiles.push_back(path);
	}
}

void EditorWindow::processDirectory(QString path, bool doCloseFiles) {
	std::cout << "hi" << std::endl;
	if (!isDirectory(path)) return;
	if (doCloseFiles) {
		int remainingFiles = Documents.size();

		OpenSourceFiles.clear();

		while (remainingFiles != 0) {
			closeFile(0);
			remainingFiles--;
		}
	}
	std::cout << "h" << std::endl;

	QString shortDir = path.split("/").last();

	setWindowTitle(shortDir + " - BRUX IDE");

	Directory = path;
	DirectoryView.setRootPath(Directory);

	auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	TreeView->setModel(&DirectoryView);
	TreeView->setRootIndex(DirectoryView.index(Directory));
	TreeView->hideColumn(3);
	int sizeOfColumn = TreeView->maximumWidth() / 4;
	TreeView->setColumnWidth(0, sizeOfColumn * 2.5f);
	TreeView->setColumnWidth(1, sizeOfColumn * 0.75f);
	TreeView->setColumnWidth(2, sizeOfColumn * 0.5f);
}

void EditorWindow::closeFile(int index) {
	DocumentViews[index]->close();
	Documents[index]->closeStream();
	closeTab(index);
	if (OpenSourceFiles.size() == 0) return; // We manually cleared this so don't erase from OpenSourceFiles.
	OpenSourceFiles.erase(OpenSourceFiles.begin() + index);
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
	newTabLayout->addWidget(DocumentViews[documentIndex]);
}

void EditorWindow::closeTab(int index) {
	QTabWidget* tabWidget = ui->centralwidget->findChild<QTabWidget*>("fileTabs");
	tabWidget->removeTab(index);
}
