# Programming Project
<hr>
## Group Members:
Matthew Langford   *mattlangford95@ufl.edu* <br>
Aaron Myska               *xmyskac@ufl.edu* <br>
Jonathan Pereyra       *jpereyra24@ufl.edu* <br>
Kevin Wong             *kevin04126@ufl.edu* <br>
Blake Johnson         *bjohnson293@ufl.edu* <br>
<hr>

##Piano Hero TODO:
-Need a GUI to display the falling notes, score, etc. <br>
-Need a way to play piano with keyboard keys (each key corresponds to a sound file of a specific note). <br>
-Need a way to define a song, eg. a format that we can save songs to and be able to read and display the notes on time. <br>
 * I think that we will have some smallest time segment (1/16th of a second for example), and then we will build the song around that time scale.
 * q,w,e,r,,,,,e,w,q would mean that for the first 1/16th a 'q' would need to be played, then the next beat would be a 'w'. When there are no letters  in between commas, that beat has no notes. Notes that you hold down may be q,q,q,q for example.
 * Multiple notes could be played each beat: qwe,rt,rt,rt,w,w,w,e
 * I just came up with this, so if you have a better implementation we can use that.

-Need a way to keep score and display it. This could also include keeping a high score. <br>
-We will all have to make atleast one song so that we have some kind of library. <br>


##NoteManager++ TODO:
-Config file that stores all parameters<br> 
-Folder class with a tag attribute<br>
-Create folders with tags that will be populated with notes automatticaly<br>
-Ability to import and export notes<br>
-Save notes<br>
-Notes Class
 * contents of the note<br>
 * folders<br>
 * tags<br>
 * file name<br>


-Tasks:
 * Read, write system of master file (Aaron)<br>
 * Command line UI (Jonathan)<br>
  * menu<br>
  * make folders (real folders - OS dependant)<br>
  * make notes<br>
  * assign tags and folders to notes
  * display notes<br>
 * Search functions (Tag, name, folder, words in text files?) (Blake)<br>
 * Initial loading (assigning notes to classes, error handling) (Matthew)<br>
 * Editing existing tags and moving folders (Kevin)<br>
 * Error Checking<br>

-Future:<br>
 * Autoscan for changes<br>
 * Auto populate tags based on note contents<br>
