export class Timer {
  constructor(displayElement) {
    this.displayElement = displayElement;
    this.startTime = 0;
    this.elapsedTime = 0;
    this.intervalId = null;
  }

  start() {
    this.startTime = Date.now() - this.elapsedTime;
    this.intervalId = setInterval(() => this.update(), 100);
  }

  pause() {
    if (this.intervalId) {
      clearInterval(this.intervalId);
      this.intervalId = null;
    }
  }

  reset() {
    this.pause();
    this.elapsedTime = 0;
    this.displayElement.textContent = "00:00";
  }

  update() {
    this.elapsedTime = Date.now() - this.startTime;
    const totalSeconds = Math.floor(this.elapsedTime / 1000);
    const minutes = Math.floor(totalSeconds / 60);
    const seconds = totalSeconds % 60;
    this.displayElement.textContent =
      `${String(minutes).padStart(2, '0')}:${String(seconds).padStart(2, '0')}`;
  }
}
