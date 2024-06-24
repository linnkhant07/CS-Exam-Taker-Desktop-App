// Timer logic
let timerInterval;
let time_counter=1;
let timerDisplay = document.getElementById('timer');
let cheaterDiaply = document.getElementById('cheaterText');

function startTimer() {
  
    clearInterval(timerInterval);
    timerInterval = setInterval(updateTimerDisplay, 1000);
  } 


function updateTimerDisplay() {
  let minutes = Math.floor(time_counter / 60);
  let seconds = time_counter % 60;
  timerDisplay.textContent = `${padTime(minutes)}:${padTime(seconds)}`;
  time_counter++;
}

function stopTimer()
{
  let minutes = Math.floor(time_counter / 60);
  let seconds = time_counter % 60;
  timerDisplay.textContent = `${padTime(minutes)}:${padTime(seconds)}`;
  clearInterval(timerInterval);
}
function padTime(time) {
  return time < 10 ? `0${time}` : time;
}

function displayCheater()
{
  if(time_counter >= 30)
    {
        cheaterDiaply.style.color = "red";
    }
}