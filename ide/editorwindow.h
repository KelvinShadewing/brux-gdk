#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include "ui_editorwindow.h"

class EditorWindow : public QMainWindow
{
	Q_OBJECT

public:
	EditorWindow(QWidget *parent = nullptr);
	~EditorWindow();

private:
	Ui::EditorWindow *ui;
	KTextEditor::Editor* TextEditorInstance;
	KTextEditor::Document* Document;
	KTextEditor::View* DocumentView;
};
#endif // EDITORWINDOW_H
