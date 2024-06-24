const {compileCpp} = require('./compile')
const { ipcRenderer, dialog } = require('electron');

const btnCanvas = document.getElementById("btnCanvas");
const btnTextEditor = document.getElementById("btnTextEditor");
let notificationsShown = false;
let lastClick = '';
btnCanvas.addEventListener('click', () => {
    
    // Send an IPC message to the main process to display the Canvas window
    ipcRenderer.send('show-canvas');
});

btnTextEditor.addEventListener('click', () => {
    // Send an IPC message to the main process to display the Text Editor window
    ipcRenderer.send('show-text-editor');
});

// Handle IPC messages from the main process
ipcRenderer.on('show-canvas', (event, arg) => {
    // Show the Canvas window and hide the Text Editor window
    
    console.log("render receives show-canvas")
    console.log("the argument is", arg)

    //document.getElementById("canvasWindow").style.display = "block";
    //document.getElementById("textEditorWindow").style.display = "none";
});

ipcRenderer.on('show-text-editor', () => {
    // Show the Text Editor window and hide the Canvas window
    document.getElementById("canvasWindow").style.display = "none";
    document.getElementById("textEditorWindow").style.display = "block";
});

let editor = document.querySelector("#editor");

editor = ace.edit(editor, {
  theme: "ace/theme/cobalt",
  mode: "ace/mode/c_cpp",
});

document.addEventListener('DOMContentLoaded', async ()=>{
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../_tests/_test_files/basic_test.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch testB.cpp');
        }
        const code = await response.text();

        //console.log(basicTestCppCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(code);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
})

const btnBasicTest = document.getElementById("btnBasicTest")
btnBasicTest.addEventListener('click', async () => {
    lastClick = "btnBasicTest";
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../_tests/_test_files/basic_test.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch baisc_test.cpp');
        }
        const basicTestCode = await response.text();

        //console.log(testBCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(basicTestCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
});

const btnTestB = document.getElementById("btnTestB")
btnTestB.addEventListener('click', async () => {
    lastClick = "btnTestB";
    try {
        // Fetch the content of basic_test.cpp
        const response = await fetch('../_tests/_test_files/testB.cpp');
        if (!response.ok) {
            throw new Error('Failed to fetch testB.cpp');
        }
        const testBCode = await response.text();

        //console.log(testBCode);
        // Set the content of the Ace editor to the fetched code
        editor.setValue(testBCode);
        // Move the cursor to the beginning of the document
        editor.moveCursorToPosition({ row: 0, column: 0 });
    } catch (error) {
        console.error(error);
        // Handle errors, such as displaying an error message to the user
    }
});


document.getElementById('saveTestB').addEventListener('click', () => {
    
    if(lastClick === 'btnTestB'){
        const code = editor.getValue();
    console.log('Save Test B Save Button Clicked');
    ipcRenderer.send('save-test-B', code);
    }
    else{
        alert('Please click testB.asm before saving asm file.')
    }
});

ipcRenderer.on('save-testB-reply', (event, message) => {
    console.log('Received save-code-reply:', message);
    if (message === 'success') {
        console.log('TestB code saved successfully');
    } else {
        console.error('Failed to save TestB code');
    }
});



const runBasicTest = document.getElementById("runBasicTest")
runBasicTest.addEventListener('click', () => {

    // Get the code from the textarea
    const code = editor.getValue();
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code, "basic_test");
    } else {
        alert('Please enter some code before submitting.');
    }
});

const runTestB = document.getElementById("runTestB")
runTestB.addEventListener('click', () => {

    // Get the code from the textarea
    const code = editor.getValue();
    console.log("code is", code);
    // Only proceed if there is code to compile and run
    if (code.trim() !== '') {
        compileCpp(code, "testB");
    } else {
        alert('Please enter some code before submitting.');
    }
});

const exitBtn = document.getElementById('exitBtn');

exitBtn.addEventListener('click', () => {
    // Send a message to the main process to request application closure
    notificationsShown = true;
    const confirmExit = window.confirm('Are you sure you want to exit the Exam?');

    if(confirmExit)
    {
        ipcRenderer.send('exit-app');
    }
});

let counterElement = document.getElementById('counter');
let modal = document.getElementById('myModal');
let off_screen_counter = 0;
let offScreen= document.getElementById('numberOftabs');

ipcRenderer.on('close-window', () => {
    notificationsShown = true;
    const confirmExit = window.confirm('Are you sure you want to exit the Exam?');

    if(confirmExit)
    {
    ipcRenderer.send('exit-app');
    }
});

ipcRenderer.on('blur-app', () => {

    
    if (!notificationsShown) {
        startTimer();
        notificationsShown = true; // Set the flag to true to indicate that the notification has been shown
        off_screen_counter++;
        modal.style.display = "block";
        updateCounter();
    }
})

function updateCounter() {
    let minutes = Math.floor(time_counter / 60);
    let seconds = time_counter % 60;
    counterElement.textContent = `${padTime(minutes)}:${padTime(seconds)}`;
    offScreen.textContent = off_screen_counter;
        setTimeout(() => {
            updateCounter();
        }, 1000); // Update the counter every second
    displayCheater();
}
ipcRenderer.on('focus-app', () => {
    stopTimer();
    notificationsShown = false;
    modal.style.display = "none";
})


/*
// Call the initializeEditor function when the DOM is ready
document.addEventListener('DOMContentLoaded', () => {
    initializeEditor();
  });*/

