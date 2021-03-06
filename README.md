# Programming Project
<hr>

To run, execute the following command in the root directory:
> $ ./src/notes++

## Group Members:
Matthew Langford   *mattlangford95@ufl.edu* <br>
Aaron Myska               *xmyskac@ufl.edu* <br>
Jonathan Pereyra       *jpereyra24@ufl.edu* <br>
Kevin Wong             *kevin04126@ufl.edu* <br>
Blake Johnson         *bjohnson293@ufl.edu* <br>
<hr>

##Notes++:
-Tasks:
 * Creating master file (Aaron)
  * Using note classes, populate a masterfile when the user makes a change.
  * An example masterfile can be found [here](https://github.com/mattlangford/Programming_Project/blob/master/masterfile).
 * Command line UI (Jonathan)
  * Command line menu, will act as the main program.
  * Allow users to make navigate through folders (real folders).
  * Move notes around.
  * Assign tags to notes.
  * Display notes.
  * Commands: help, exit, mkdir FOLDERNAME, mv FILENAME TO_FOLDERNAME, tag add FILE TAG, tag rm FILE TAG, new FILE (run gedit with new text file, afterwards allow tag association).
 * Search functions (Tag, folder, keyword) (Blake)
  * Calls methods in Note class for each Note.
  * Should display basic info from the note. If searching for keywords, it should display a google like preview of matching notes.
 * Initial loading (Matthew)
  * Check for discontinuities between masterfile and file tree.
  * Prompt user to resolve issues between file .
 * Scan folder tree for files (Kevin)
  * Create note classes for all text files in the tree.
 * Error Checking (everyone will do this)

-Future:<br>
 * Auto populate tags based on note contents
 * Better search functioins (auto correcting, etc.)
