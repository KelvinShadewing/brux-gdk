#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <KTextEditor/Document>
#include <KTextEditor/Editor>
#include <KTextEditor/View>
#include <KSyntaxHighlighting/Repository>

#include <vector>

#include "ui_editorwindow.h"

/** \class EditorWindow
 * The main window for the brux IDE.
 */
class EditorWindow : public QMainWindow
{
	Q_OBJECT
public slots:
	/**
	 * Opens a given file from the directory view in the text editor.
	 * @see DirectoryView
	 */
	void handleDoubleClick(QModelIndex index);

	/**
	 * Opens a given directory as a project. This enables testProject to work.
	 * @see testProject()
	 */
	void openDirectory(bool checked = false);

	/**
	 * Opens a file in the built-in text editor provided by KTextEditor (from KDE Frameworks 5).
	 */
	void openFile(bool checked = false);

	/**
	 * Executes the open project using brux.
	 * This expects brux to be within the PATH environment variable.
	 */
	void testProject();
public:
	/**
	 * Constructor for the window.
	 */
	EditorWindow(QWidget *parent = nullptr, QString projectDirectory = "");

	/**
	 * Destructor for the window.
	 */
	~EditorWindow();

	/**
	 * Merely checks that the path given not only exists, but is also a file rather than a directory.
	 */
	bool isFile(QString path);

	/**
	 * Same as isFile but for directories instead.
	 */
	bool isDirectory(QString path);

	/**
	 * Checks that the path is a file that exists along with checking that the file extension is a tiled extension.
	 */
	bool isTilemap(QString path);

	/**
	 * Handles the file opening behaviour.
	 */
	void processFile(QString path, QString name = "", bool newFile = false);

	/**
	* Handles the directory opening behaviour.
	*/
	void processDirectory(QString path, bool doCloseFiles = true);

	/**
	 * Closes a file at the given index.
	 */
	void closeFile(int index);

	/**
	 * Creates a new tab with a name and index
	 */
	void createTab(QString name, int documentIndex);

	/**
	 * Closes a tab at the given index.
	 */
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
