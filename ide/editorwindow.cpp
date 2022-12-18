#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <iostream>
#include <fstream>
#include <QDir>

#include <KHelpMenu>
#include <KAboutData>

EditorWindow::EditorWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditorWindow) {
	ui->setupUi(this);
	KHelpMenu* Help = new KHelpMenu(this, KAboutData::applicationData());
	ui->menubar->addMenu(Help->menu());

	std::cout << Directory.toStdString() << std::endl;
	DirectoryView.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	DirectoryView.setRootPath(Directory);

	auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	TreeView->setModel(&DirectoryView);
	TreeView->setRootIndex(DirectoryView.index(Directory));

	connect(TreeView, &QTreeView::doubleClicked, this, &EditorWindow::handleDoubleClick);

	TextEditorInstance = KTextEditor::Editor::instance();
	openFile("", true);
	openFile("", true);
}

EditorWindow::~EditorWindow() {
	delete ui;
}

void EditorWindow::handleDoubleClick(QModelIndex index) {
	// Always get column 0 (name)
	index = index.siblingAtColumn(0);
	QTreeView* treeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	QString item = treeView->model()->data(index).toString();
	std::cout << Directory.toStdString() << "/" << item.toStdString() << std::endl;
}

bool EditorWindow::isFile(QString path) {
	QDir FileCheck{path};
	FileCheck.setFilter(QDir::Files);
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

void EditorWindow::openFile(QString path, bool newFile) {
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
	DocumentTitles.push_back(name);
	newTabLayout->addWidget(DocumentViews[documentIndex]);
}
