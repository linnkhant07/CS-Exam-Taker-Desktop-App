# Installation:

- Have CMake and GCC working
- Get node.js from [here](https://nodejs.org/en)
- Run `npm install` in your terminal to install the electron framework
- Use `npm start` to launch the program

# Documentation/Functionalities:

## Index.js functionalities:

_File that manages the main window_

**createCanvasView():**

- creates a new object of BrowserView named canvasView, using the functions from the object it loads the canvas website from PCC using: ".webContents.loadURL('url-goes-here')"
- calls mainWindow variable and using ".setBrowserView(BrowserView_obj)", it adds the previously created variable into the mainWindow
- calls .setBounds for the canvasView object to set the bounds/space it will use in the main window. "setBounds(x,y,width,height)"
- Lastly it saves a referencce to the canvas BrowserView in the main window "mainWindow.canvasView=canvasView"

**const CreateWindow = ()=> {} :**

- Creates a browser window object, intializing width and height. Adds characteristic of alwaysOnTop, resizable, and sets the webPreferences: nodeIntegration to true and contextIsolation to false. and sets its preload to specifically load the preload.js file before anything else.
- It will then load the index.html file.
- Events that the MainWindow handle:

  - **mainWindow.on ('blur', event)=>{} :**

  As of right now in case the user goes out of the window/loses focus it will destroy/close the mainWindow which will esentially terminate the program

  - **mainWindow.on('focus', () => {}) :**

  Tracks the time in which the user has been using the app. In case they are able to exit it

  - **ipcMain.on('show-canvas', (event,arg) => {}) :**

  Will display the canvas window on top of the text editor whenver the button is clicked

  - **ipcMain.on('show-text-editor', () => {}) :**

  In the case it shows the text editor, this function will just hide the canvas view until its called again

  - **ipcMain.on('exit-app', (event) => {}):**

  It will prevent the capp from straight up closing and it will also display an alert box that will ask the user if they want to exit the program or not

**app.on('window-all-closed', () => {}) :**

    This function is in charge to close the application down completely when students close down their application

**app.whenReady().then(() => {}):** 1. When the application has finished initialization it will be ready to create windows and then is when this function fires. 2. Then it will verify that no window has been created nor opened and it will display the window and it will be in charge of loading the browser and the workspace for the students
**showDialog(message){}:**

Show dialog is in charge of displaying the message passed as an argument as a notification by using the Electron framework

**clipBoardLock (){}:**

This function is in charge of replacing anything that has been copied to the clipboard into the string inside of the write text function, and then it will replace that by using the clipboard.readText function to put it as the new copied text into the clipboard

## Timer.js functionalities:

_Initializes variables as the maximum time for the exam in totalTimeInSeconds (it is defaulted at 15 minutes, and it only takes seconds as the determiner of the time and it also gets the id of the html sections._

**startTimer(){}:**

- Initializes an examTime variable that will call the parseInt function (which will convert the input into a valid number), then it'll take the examTimeInput variable (which takes gets its values from HTML)
- Checks if the examTime is valid by checking if it larger than 0
  - sets the totalTime in seconds variable to be the input \* 60
  - sets the remaining time to be equal to the recently calculated time
- Else it will display an alert of invalid time input

**updateTimerDisplay():**

- Obtains the actual time from the secondsRemaining variable and tranlates it to the minutes and seconds that are actually left to turn in the exam
- It calls pad time to format the time value
- It will also replace the current displayed text
- If the time is 0 it will pop up the warning to turn in the exam
- Everytime it is called it will substract 1 from the secondsRemaining variable

**padTime (time):**

returns a string depending on the value passed of time, if the time i less than ten it will return a string with a 0 ahead of it, if it is bigger than 10 it will just return the number that is bigger than 12

## Compiler.js Functionalities:

_The compile file only has one single function._

**_function compileCpp (code,fileName):_**

- We declare a variable called cmake which is going to execute the compilation process using the provided CMakeLists.txt and gcc
- The next 2 lines of code are in charge of displaying the data that has been received when reading the file and it will log either errors or what data has been sucessfully received it into the console.
- The code argument is going to be checked afterwards and it will be in charge of returning the exit code, if it returns a 0 then we can continue the process
  - Else it will throw the error code into the console
- The next step inside of the if statement with return code 0, is to declare 2 variables the buildDir one will store the path to the build directory based on the current directory. And the make variable that works very similar to cmake and is the one in charge of spotting the errors during the compilation process
- The next few lines inside of the function are the ones in charge of spotting issues when building the program or when running it successfully
- The last big component of the program is when the program is sucessfully compiled and is in charge of running it, inside of this we are going to declare the variables that are going to capture the program output, if it is not able to run it it will return the exit code or the error that the program is having.

## Render.js Functionalities:

_The render file is in charge of everything related to the interactive/visual part of the program._

At the beggining of it we declare the ipc variable that is going to call the electron framework, and it will be in charge of connecting everything in the application.

We also have the compileCpp variable that is going to be initialized by requiring the compile.js, and it will eventually be used to call the compileCpp function from the compiler.js.

And after that we declare the variables in charge of keeping track of the html buttons, btnCanvas and btnTextEditor.

**btnCanvas.addEventListener('click', () => {}):**

Is going to tell the ipc variable to call the process to display the canvas window that is inside of the index.js file
**btnTextEditor.addEventListener('click', () => {}):**
Is going to do the same thing as the Canvas btn but calling the textEditor function in index.js

**ipcRenderer.on('show-text-editor', () => {} ):**

- Is going to make the canvas window to not interfeer into the interface.
- We declare an editor variable and we initialize it using ace.edit, and the theme can be set to any theme available in its api, however the mode is set to be for cpp files

**document.addEventListener('DOMContentLoaded', async ()=>{}):**

- This function will be in charge of loading the files into the editor, it uses fetch in order to do that task. This operation in handled inside of try and catch block so in case the file is unnable to open it will fire an error message into the console. When the fetch is successful it will set the code inside of the text editor to be the poly file.
- We declare variables in charge of handling the files inside of the app, in this case we have basicTest, testB and poly. Each of them have a function that will be in charge of the case in which these buttons are clicked, following a very similar structure to the previous event listener, which is going to fetch the data into the text editor and set the cursor to be on the top left corner and it will make the text in it to be the one from the button that was clicked.
- There is also a submit variable that will be in charge of obtaining the code from the text editor into a code variable, it will check if the code is able to compile or not, if no code is detected that process won't be called.
- There is 2 run buttons for each test file. Inside of them we are going to get the code from the text editor, if the code is not empty it will run the compile process from the compile.js file or if the code is empty it will fire an alert asking to add code into the text editor.
- And finally there is the functionalities for the exit button, which will only tell the ipc variable to call the exit-app process from the index.js file
