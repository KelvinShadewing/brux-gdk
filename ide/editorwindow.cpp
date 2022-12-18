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
	Document = TextEditorInstance->createDocument(this);
	auto ScriptTab = ui->centralwidget->findChild<QWidget*>("scripting");

	// kde how the hell does this work???
	DocumentView = Document->createView(nullptr);
	ScriptTab->layout()->addWidget(DocumentView);
	DocumentView->updateGeometry();
	ScriptTab->updateGeometry();
}

EditorWindow::~EditorWindow() {
	delete ui;
}

void EditorWindow::handleDoubleClick(QModelIndex index) {

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

void EditorWindow::openFile(QString path) {}
