const { app, BrowserWindow, BrowserView, ipcMain, dialog, globalShortcut } = require('electron');
const path = require('node:path');
const fs = require('fs');
const cloneAllRepos = require('./fetchFiles');
const { compileCpp } = require('./compile');

let mainWindow;
let canvasView;

// Handle creating/removing shortcuts on Windows when installing/uninstalling.
if (require('electron-squirrel-startup')) {
  app.quit();
}

async function main() {
  try {
    // Await the completion of cloneAllRepos
    await cloneAllRepos();
    
    app.whenReady().then(() => {
      createWindow();

      app.on('activate', () => {
        if (BrowserWindow.getAllWindows().length === 0) {
          createWindow();
        }
      });
    });

    app.on('window-all-closed', () => {
      if (process.platform !== 'darwin') {
        app.quit();
        globalShortcut.unregisterAll();
      }
    });

    app.on('will-quit', () => {
      globalShortcut.unregisterAll();
    });
  } catch (error) {
    console.error('Error during initialization:', error);
    app.quit();
  }
}

function createWindow() {
  mainWindow = new BrowserWindow({
    width: 1600,
    height: 1000,
    kiosk: false, // Comment this out if it is too annoying
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(__dirname, 'preload.js'),
    },
  });

  mainWindow.loadFile(path.join(__dirname, 'index.html'));

  mainWindow.on('close', handleWindowClose);
  mainWindow.on('blur', () => mainWindow.webContents.send('blur-app'));
  mainWindow.on('focus', () => mainWindow.webContents.send('focus-app'));

  createCanvasView();

  // Listen for IPC messages from the renderer process
  ipcMain.on('show-canvas', showCanvas);
  ipcMain.on('show-text-editor', hideCanvas);
  ipcMain.on('exit-app', () => mainWindow.destroy());

  ipcMain.on('save-test-B', (event, code) => saveFile(event, code, '../_tests/_test_files/testB.cpp', 'save-testB-reply'));
  ipcMain.on('save-student-file', (event, code) => saveFile(event, code, '../includes/poly/poly_student.cpp', 'save-student-file-reply'));

  // Open the DevTools.
  mainWindow.webContents.openDevTools();
}

function createCanvasView() {
  canvasView = new BrowserView();
  canvasView.webContents.loadURL('https://canvas.pasadena.edu');
  mainWindow.setBrowserView(canvasView);
  canvasView.setBounds({ x: 32, y: 215, width: 0, height: 0 });
  mainWindow.canvasView = canvasView;
}

function showCanvas() {
  canvasView.setBounds({ x: 32, y: 215, width: 1000, height: 770 });
}

function hideCanvas() {
  canvasView.setBounds({ x: 0, y: 0, width: 1, height: 1 });
}

function handleWindowClose(event) {
  event.preventDefault(); // Prevent the window from closing
  dialog.showMessageBox(mainWindow, {
    type: 'warning',
    message: 'Are you sure you want to exit the exam?',
    buttons: ['Yes', 'No'],
    defaultId: 1,
    cancelId: 1
  }).then((response) => {
    if (response.response === 0) {
      mainWindow.destroy();
    }
  });
}

function saveFile(event, code, filePath, replyChannel) {
  const fullPath = path.join(__dirname, filePath);
  fs.writeFile(fullPath, code, (err) => {
    if (err) {
      console.error('Failed to save file', err);
      event.reply(replyChannel, 'fail');
      return;
    }
    console.log('File saved successfully');
    event.reply(replyChannel, 'success');
  });
}


// Call the main function to start the application
main();
