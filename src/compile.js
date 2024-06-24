const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

function compileCpp(code, fileName) {
    const parentDir = path.resolve(__dirname, '..');

    // Execute compilation process using provided CMakeLists.txt and cmake
    const cmake = spawn('/opt/homebrew/bin/cmake', ['-S', '.', '-B', 'build'], { cwd: parentDir });

    cmake.stdout.on('data', (data) => {
        console.log(`cmake stdout: ${data}`);
    });

    cmake.stderr.on('data', (data) => {
        console.error(`cmake stderr: ${data}`);
    });

    cmake.on('close', (code) => {
        if (code === 0) {
            console.log('CMake configuration successful! Now trying to run the build');

            // Execute build process using cmake --build
            const buildDir = path.resolve(parentDir, 'build');
            const make = spawn('/opt/homebrew/bin/cmake', ['--build', buildDir], { cwd: parentDir });

            make.stdout.on('data', (data) => {
                console.log(`make stdout: ${data}`);
            });

            make.stderr.on('data', (data) => {
                console.error(`make stderr: ${data}`);
            });

            make.on('close', (code) => {
                if (code === 0) {
                    console.log('Build successful! Now running the compiled program');

                    // Execute the compiled program
                    const compiledProgram = spawn(path.join(buildDir, 'bin', fileName), [], { cwd: parentDir });

                    let output = '';
                    compiledProgram.stdout.on('data', (data) => {
                        console.log(`Program output: ${data}`);
                        output += data.toString();
                    });

                    compiledProgram.stderr.on('data', (data) => {
                        console.error(`Program error: ${data}`);
                    });

                    compiledProgram.on('close', (code) => {
                        console.log(`Program exited with code ${code}`);
                        // Display the program output
                        console.log("program output is", output);
                        document.getElementById('codeOutput').innerText = output;
                    });
                } else {
                    console.error(`Build failed with code ${code}`);
                }
            });
        } else {
            console.error(`CMake configuration failed with code ${code}`);
        }
    });
}

module.exports = { compileCpp };
