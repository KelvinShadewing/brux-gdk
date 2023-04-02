#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KSyntaxHighlighting/Repository>

#include <map.h>
#include <maprenderer.h>
#include <vector>

#include "ui_editorwindow.h"

class EditorWindow : public QMainWindow
{
	Q_OBJECT
public slots:
	void handleDoubleClick(QModelIndex index);

	void openDirectory(bool checked = false);

	void openFile(bool checked = false);
public:
	EditorWindow(QWidget *parent = nullptr, QString projectDirectory = getenv("HOME"));
	~EditorWindow();

	bool isFile(QString path);

	bool isDirectory(QString path);

	bool isTilemap(QString path);

	void processFile(QString path, QString name = "", bool newFile = false);

	void processDirectory(QString path, bool doCloseFiles = true);

	void closeFile(int index);

	void createTab(QString name, int documentIndex);

	void closeTab(int index);
private:
	Ui::EditorWindow *ui;
	KTextEditor::Editor* TextEditorInstance;
	std::vector<KTextEditor::Document*> Documents;
	std::vector<KTextEditor::View*> DocumentViews;
	std::vector<QString> OpenSourceFiles;
	std::vector<QString> OpenTilemapFiles;
	QString Directory;
	QFileSystemModel DirectoryView;
};
#endif // EDITORWINDOW_H
