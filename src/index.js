const { app, BrowserWindow, BrowserView, ipcMain, dialog } = require('electron');
const path = require('node:path');
const fs = require('fs');

//for disabling shortcuts
const { globalShortcut } = require('electron');
const { compileCpp } = require('./compile');

let mainWindow;
let canvasView;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

function createCanvasView() {
  // Create a BrowserView for the canvas
  canvasView = new BrowserView();

  // Set the web contents of the BrowserView to the Canvas webpage
  canvasView.webContents.loadURL('https://canvas.pasadena.edu');

  // Attach the BrowserView to the main window
  mainWindow.setBrowserView(canvasView);

  // Set the bounds of the BrowserView
  canvasView.setBounds({ x: 32, y: 215, width: 0, height: 0 });


  // Store a reference to the canvas BrowserView in the main window object
  mainWindow.canvasView = canvasView;
}

const createWindow = () => {
  // Create the browser window.
  mainWindow = new BrowserWindow({
    width: 1600,

    height: 1000,
    //alwaysOnTop: true,
      kiosk: false, //comment this out if it is too annoying
      webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(__dirname, 'preload.js'),
    },
  });

  // and load the index.html of the app.
  mainWindow.loadFile(path.join(__dirname, 'index.html'));

  // Alert when the user tries to close the app
  mainWindow.on('close', (event) => {
    
    event.preventDefault(); // Prevent the window from closing
    dialog.showMessageBox(mainWindow, {
    type: 'warning',
    message: 'Are you sure you want to exit the exam?',
    buttons: ['Yes', 'No'],
    defaultId: 1,
    cancelId: 1
  }).then((response) => {
    if (response.response === 0) {
      // User clicked 'Yes', close the window
      mainWindow.destroy();
    }
  });
});

mainWindow.on('blur', () => {

  mainWindow.webContents.send('blur-app');
});

// Track when the app gains focus
mainWindow.on('focus', () => {
  // User returned to the app
  mainWindow.webContents.send('focus-app');
  //notificationShown = false;
});
  // Create and attach the canvas BrowserView
  createCanvasView();

  // Listen for IPC messages from the renderer process
  ipcMain.on('show-canvas', (event,arg) => {

    canvasView.setBounds({ x: 32, y: 215, width: 1000, height: 770 });
    //x=32, y:215
  });

  ipcMain.on('show-text-editor', () => {
      // Logic to show the Text Editor window
      canvasView.setBounds({ x: 0, y: 0, width: 1, height: 1 });
  });

  // Alert when the user tries to exit the app
  ipcMain.on('exit-app', (event) => {
    mainWindow.destroy();
  });

  // Open the DevTools.
  mainWindow.webContents.openDevTools();

  ipcMain.on('save-ASM', (event,code)=>{
    const filePath = path.join(__dirname, '../includes/asm_files/functions.asm');
    fs.writeFile(filePath, code, (err) => {
      if (err) {
          console.error('Failed to save file', err);
          event.reply('save-ASM-reply', 'fail');
          return;
      }
      console.log('File saved successfully');
      event.reply('save-ASM-reply', 'success');

      // Run the compile function
  });
});

ipcMain.on('save-test-B', (event,code)=>{
  const filePath = path.join(__dirname, '../_tests/_test_files/testB.cpp');
  fs.writeFile(filePath, code, (err) => {
    if (err) {
        console.error('Failed to save file', err);
        event.reply('save-testB-reply', 'fail');
        return;
    }
    console.log('File saved successfully');
    event.reply('save-testB-reply', 'success');

    // Run the compile function
});
});
  /*
  // Create a BrowserView
  const browserView = new BrowserView();
  mainWindow.setBrowserView(browserView);
  browserView.setBounds({ x: 500, y: 0, width: 700, height: 800 });

  // Load Canvas URL into the BrowserView
  browserView.webContents.loadURL('https://canvas.pasadena.edu');*/


  // Optional: Open DevTools for debugging
  //browserView.webContents.openDevTools();
};


// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {
  createWindow();

  // On OS X it's common to re-create a window in the app when the
  // dock icon is clicked and there are no other windows open.
  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }

  const win = new BrowserWindow({ width: 800, height: 600 })

  const view = new BrowserView()
  win.setBrowserView(view)
  view.setBounds({ x: 0, y: 0, width: 300, height: 300 })
  view.webContents.loadURL('https://electronjs.org')
  });
});

// second helper to prevent the app from loosing focus
// app.on('browser-window-blur', (event, bw) => {
//   bw.restore()
//   bw.focus()

//   globalShortcut.unregisterAll();
// })

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit();
    globalShortcut.unregisterAll();
  }
});

app.on('browser-window-focus', function () {
  globalShortcut.register("Alt+Tab", () => {
    // Prevent default behavior
    // Optionally, we can display a message 
    showDialog('Alt+Tab is disabled in this application.');
  });
  globalShortcut.register("CommandOrControl+R", () => {
      showDialog("CommandOrControl+V is pressed: Shortcut Disabled");
  });
  globalShortcut.register("F5", () => {
      showDialog("F5 is pressed: Shortcut Disabled");
  });
});

app.on('will-quit', function(){
  globalShortcut.unregisterAll();
})


// Function to display notifications using Electron's dialog module
function showDialog(message) {
  dialog.showMessageBox(mainWindow, {
    type: 'info',
    message: message,
    buttons: ['OK']
  });
}
// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and import them here.