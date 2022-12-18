#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <iostream>
#include <fstream>

#include <QDir>
#include <QFileDialog>

#include <KHelpMenu>
#include <KAboutData>

EditorWindow::EditorWindow(QWidget *parent, QString projectDirectory) : QMainWindow(parent), ui(new Ui::EditorWindow), Directory(projectDirectory) {
	ui->setupUi(this);
	QMenu* newMenu = new QMenu("File");
	connect(newMenu->addAction("Open Folder"), SIGNAL(triggered()) , this, SLOT(openDirectory()));
	KHelpMenu* Help = new KHelpMenu(this, KAboutData::applicationData());
	ui->menubar->addMenu(newMenu);
	ui->menubar->addMenu(Help->menu());

	DirectoryView.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	DirectoryView.setRootPath(Directory);

	auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	TreeView->setModel(&DirectoryView);
	TreeView->setRootIndex(DirectoryView.index(Directory));
	connect(TreeView, &QTreeView::doubleClicked, this, &EditorWindow::handleDoubleClick);

	TextEditorInstance = KTextEditor::Editor::instance();
}

EditorWindow::~EditorWindow() {
	delete ui;
}

void EditorWindow::handleDoubleClick(QModelIndex index) {
	// Always get column 0 (name)
	index = index.siblingAtColumn(0);

	QTreeView* treeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	QString item = treeView->model()->data(index).toString();

	openFile(DirectoryView.filePath(index), item);
}

void EditorWindow::openDirectory(bool checked) {
	std::cout << "dirtime" << std::endl;
	std::cout << checked << std::endl;
	QString newDir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), getenv("HOME"), QFileDialog::ShowDirsOnly);

	if (!newDir.isEmpty()) {
		Directory = newDir;
		DirectoryView.setRootPath(Directory);

		auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
		TreeView->setModel(&DirectoryView);
		TreeView->setRootIndex(DirectoryView.index(Directory));
	}
}

bool EditorWindow::isFile(QString path) {
	QFile FileCheck{path};
	std::cout << path.toStdString() << ": " << FileCheck.exists() << std::endl;
	return FileCheck.exists();
}

bool EditorWindow::isTilemap(QString path) {
	// Behold, suffering
	bool fileExists = isFile(path);
	if (!fileExists) return false;

	if (!path.endsWith(".json")) return false;

	std::ifstream file;
	file.open(path.toStdString(), std::ifstream::in);

	file.seekg(0, file.end);
	int Length = file.tellg();
	file.seekg(0, file.beg);

	char* buffer = new char[Length];

	file.read(buffer, Length);

	QString contents = buffer;

	delete[] buffer;

	if (contents.contains("\"tiledversion\"")) return true;
	return false;
}

void EditorWindow::openFile(QString path, QString name, bool newFile) {
	int vecSize = Documents.size();
	std::cout << path.toStdString() << std::endl;
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

	QFile fileExistsCheck{path};
	QDir dirExistsCheck{path};
	if (fileExistsCheck.exists() && !dirExistsCheck.exists()) {
		Documents.push_back(TextEditorInstance->createDocument(this));
		Documents[vecSize]->openUrl(QUrl("file://" + path));
		DocumentViews.push_back(Documents[vecSize]->createView(nullptr));
		createTab(name, vecSize);
	}
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
