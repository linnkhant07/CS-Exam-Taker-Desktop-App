const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

function compileCpp(fileName) {
    const parentDir = path.resolve(__dirname, '..');
    let output = '';

    function clearOutput() {
        output = '';
    }

    function updateOutput(data) {
        output += data.toString();
        document.getElementById('codeOutput').innerText = output;
    }

    function runCommand(command, args, cwd) {
        return new Promise((resolve, reject) => {
            const process = spawn(command, args, { cwd });

            process.stdout.on('data', (data) => {
                console.log(`${command} stdout: ${data}`);
                updateOutput(data);
            });

            process.stderr.on('data', (data) => {
                console.error(`${command} stderr: ${data}`);
                updateOutput(data);
            });

            process.on('close', (code) => {
                if (code === 0) {
                    resolve();
                } else {
                    reject(new Error(`${command} failed with code ${code}`));
                }
            });
        });
    }

    // IMPORTANT: for deployment and packaging, specify the complete path for cmake
    return runCommand('cmake', ['-S', '.', '-B', 'build'], parentDir)
        .then(() => {
            clearOutput();
            return runCommand('cmake', ['--build', path.resolve(parentDir, 'build')], parentDir);
        })
        .then(() => {
            clearOutput();
            return runCommand(path.join(path.resolve(parentDir, 'build'), 'bin', fileName), [], parentDir);
        })
        .then(() => {
            return output;
        })
        .catch((error) => {
            console.error(error);
            return output;
        });
}

module.exports = { compileCpp };
