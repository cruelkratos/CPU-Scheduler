const { ipcRenderer } = require('electron');

const runSchedulerBtn = document.getElementById('runSchedulerBtn');
const resultElement = document.getElementById('result');
const averageBox = document.getElementById('averageBox');
const averageTATElement = document.getElementById('averageTAT');
const averageWTElement = document.getElementById('averageWT');
const cpuOverheadElement = document.getElementById('cpuOverhead'); // Added for displaying CPU overhead

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
        resultElement.classList.add('text-danger');
        resultElement.classList.remove('text-success');
    } else {
        console.log('Scheduler result:', result);
        const { processes, averageTAT, averageWT, schedulingOverhead } = result;
        resultElement.innerText = `Processes: ${JSON.stringify(processes, null, 2)}`;
        
        averageTATElement.innerText = `Average Turnaround Time: ${averageTAT}`;
        averageWTElement.innerText = `Average Waiting Time: ${averageWT}`;
        cpuOverheadElement.innerText = `Scheduling Overhead: ${schedulingOverhead.toFixed(6)} s`; // Updated to show float value with units

        averageBox.style.display = 'block';
        
        resultElement.classList.add('text-success');
        resultElement.classList.remove('text-danger');
    }
});
