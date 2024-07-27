const simpleGit = require('simple-git')
const path = require('path')
const dotenv = require('dotenv');
const fs = require('fs');
const rimraf = require('rimraf');

dotenv.config()

cloneRepos = [
    
    {repo: process.env.INCLUDES_REPO,
    cloneFolder: "includes",
    gitHubToken: process.env.INCLUDES_TOKEN},
    
    
    {repo: process.env.TESTFILES_REPO,
    cloneFolder: "_tests",
    gitHubToken: process.env.TESTFILES_TOKEN}
]


async function removeDirectory(directoryPath) {
    if (fs.existsSync(directoryPath)) {
        try {
            await fs.promises.rm(directoryPath, { recursive: true, force: true });
            console.log(`Existing ${directoryPath} directory removed`);
        } catch (error) {
            console.error(`Error removing directory ${directoryPath}:`, error);
        }
    }
}

async function cloneRepo(repoConfig) {
    const repoUrl = `https://${repoConfig.gitHubToken}:x-oauth-basic@github.com/${repoConfig.repo}`;
    const localPath = path.resolve(__dirname, '../', repoConfig.cloneFolder);

    const git = simpleGit();

    try {
        // Remove the directory if it exists
        await removeDirectory(localPath);

        await git.clone(repoUrl, localPath);
        console.log(`Repository cloned successfully to ${localPath}`);
    } catch (error) {
        console.error(`Error cloning repository ${repoUrl}:`, error);
    }
}

async function cloneAllRepos() {
    for (const repoConfig of cloneRepos) {
        await cloneRepo(repoConfig);
    }
}

module.exports = cloneAllRepos;


