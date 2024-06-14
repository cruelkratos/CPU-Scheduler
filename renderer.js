const { ipcRenderer } = require('electron');

const runSchedulerBtn = document.getElementById('runSchedulerBtn');
const resultElement = document.getElementById('result');

runSchedulerBtn.addEventListener('click', () => {
    const algorithm = document.getElementById('algorithmSelect').value;
    const input = document.getElementById('processInput').value;

    console.log('Sending runScheduler event with algorithm:', algorithm);
    console.log('Input:', input);

    ipcRenderer.send('runScheduler', { algorithm, input });
});

ipcRenderer.on('schedulerResult', (event, { error, result }) => {
    if (error) {
        console.log(`Scheduler error: ${error}`);
        resultElement.innerText = `Error: ${error}`;
    } else {
        console.log('Scheduler result:', result);
        resultElement.innerText = JSON.stringify(result, null, 2);
    }
});
