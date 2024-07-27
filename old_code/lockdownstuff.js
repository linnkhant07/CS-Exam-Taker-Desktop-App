app.whenReady().then(() => {
    createWindow();
    registerGlobalShortcuts();

    app.on('activate', () => {
      if (BrowserWindow.getAllWindows().length === 0) {
        createWindow();
      }
    });
  });

function registerGlobalShortcuts() {
    app.on('browser-window-focus', () => {
      globalShortcut.register("Alt+Tab", () => showDialog('Alt+Tab is disabled in this application.'));
      globalShortcut.register("CommandOrControl+R", () => showDialog("CommandOrControl+R is pressed: Shortcut Disabled"));
      globalShortcut.register("F5", () => showDialog("F5 is pressed: Shortcut Disabled"));
    });
  }
  
  function showDialog(message) {
    dialog.showMessageBox(mainWindow, {
      type: 'info',
      message: message,
      buttons: ['OK']
    });

}