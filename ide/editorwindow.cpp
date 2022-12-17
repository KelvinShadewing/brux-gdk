#include "editorwindow.h"
#include "ui_editorwindow.h"

#include <iostream>
#include <QDir>

EditorWindow::EditorWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditorWindow) {
	ui->setupUi(this);

	std::cout << Directory.toStdString() << std::endl;
	DirectoryView.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
	DirectoryView.setRootPath(Directory);

	auto TreeView = ui->centralwidget->findChild<QTreeView*>("treeView");
	TreeView->setModel(&DirectoryView);
	TreeView->setRootIndex(DirectoryView.index(Directory));

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

bool EditorWindow::isFile(QString path) {
	return false;
}

bool EditorWindow::isTilemap(QString path) {
	return false;
}

void EditorWindow::openFile(QString Path) {}

