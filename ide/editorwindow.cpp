#include "editorwindow.h"
#include "ui_editorwindow.h"

EditorWindow::EditorWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::EditorWindow) {
	ui->setupUi(this);

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

