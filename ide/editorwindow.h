#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>

#include <tiled/map.h>
#include <tiled/maprenderer.h>
#include <tiled/tiled.h>

#include <vector>

#include "ui_editorwindow.h"

class EditorWindow : public QMainWindow
{
	Q_OBJECT
public slots:
	void handleDoubleClick(QModelIndex index);
public:
	EditorWindow(QWidget *parent = nullptr);
	~EditorWindow();

	bool isFile(QString path);

	bool isTilemap(QString path);

	void openFile(QString path);
private:
	Ui::EditorWindow *ui;
	KTextEditor::Editor* TextEditorInstance;
	KTextEditor::Document* Document;
	KTextEditor::View* DocumentView;
	QStringList DocumentTitles;
	std::vector<Tiled::MapRenderer> Renderers;
	QString Directory = getenv("PWD");
	QFileSystemModel DirectoryView;
};
#endif // EDITORWINDOW_H
