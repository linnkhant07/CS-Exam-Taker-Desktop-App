const monaco = require('node_modules/monaco-editor/esm/vs/editor/editor.api.js');

function initializeEditor(){
    
    monaco.editor.create(document.getElementById('container'), {
    value: "#include <iostream>\n\nusing namespace std;\n\nint main() {\n\tcout << \"Hello, world!\" << endl;\n\treturn 0;\n}",
    language: 'cpp'
  });
}

module.exports = {initializeEditor}
