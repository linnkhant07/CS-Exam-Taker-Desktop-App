const { spawn } = require('child_process');
const fs = require('fs');
const path = require('path');

function compileCpp(code, fileName) {
    const parentDir = path.resolve(__dirname, '..');

    const cmakeArgs = [
        '-DCMAKE_BUILD_TYPE:STRING=Debug',
        '-DCMAKE_C_COMPILER:FILTEPATH=C:/MinGW/bin/gcc.exe',
        '-DCMAKE_CXX_COMPILER:FILEPATH=C:/MinGW/bin/g++.exe',
        '-DCMAKE_ASM_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.33/bin/Hostx86/x86/cl.exe',
        '-S', '.',
        '-B', 'build',
        '-G', 'Ninja'
    ];
    
    // Spawn the cmake process
    const cmake = spawn('cmake', cmakeArgs, {cwd: parentDir});

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
            const make = spawn('cmake', ['--build', 'build'], { cwd: parentDir });

            make.stdout.on('data', (data) => {
                console.log(`make stdout: ${data}`);
                document.getElementById('codeOutput').innerText = data.toString();
            });

            make.stderr.on('data', (data) => {
                console.error(`make stderr: ${data}`);
                document.getElementById('codeOutput').innerText = data.toString();
            });

            make.on('close', (code) => {
                if (code === 0) {
                    console.log('Build successful! Now running the compiled program');

                    // Execute the compiled program
                    const compiledProgram = spawn(path.join(buildDir, fileName), [], { cwd: parentDir });

                    let output = '';
                    compiledProgram.stdout.on('data', (data) => {
                        console.log(`Program output: ${data}`);
                        output += data.toString();
                    });

                    compiledProgram.stderr.on('data', (data) => {
                        console.error(`Program error: ${data}`);
                        output += data.toString();
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