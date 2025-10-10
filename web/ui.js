export class UI {
  constructor() {
    this.playPauseButton = document.getElementById("play-pause-button");
    this.restartButton = document.getElementById("restart-button");
    this.clearButton = document.getElementById("clear-button");
    this.entityOptions = document.querySelectorAll(".entity-option");
    this.gameOverModal = document.getElementById("game-over-modal");
    this.extinctionMessage = document.getElementById("extinction-message");
    this.modalRestartButton = document.getElementById("modal-restart-button");
  }

  setPlayPauseText(text) {
    this.playPauseButton.textContent = text;
  }

  selectEntity(entityType) {
    this.entityOptions.forEach((option) => {
      const optionType = parseInt(option.dataset.entity);
      if (optionType === entityType) {
        option.classList.add("selected");
      } else {
        option.classList.remove("selected");
      }
    });
  }

  deselectAllEntities() {
    this.entityOptions.forEach((option) => {
      option.classList.remove("selected");
    });
  }

  enableEntitySelection() {
    this.entityOptions.forEach((option) => {
      option.classList.remove("disabled");
    });
  }

  disableEntitySelection() {
    this.entityOptions.forEach((option) => {
      option.classList.add("disabled");
    });
  }

  showGameOver(extinctEntity) {
    const message =
      extinctEntity === "Raposas" || extinctEntity === "Grama"
        ? `${extinctEntity} foi extinta!`
        : `${extinctEntity} foram extintos!`;
    this.extinctionMessage.textContent = message;
    this.gameOverModal.classList.add("visible");
  }

  hideGameOver() {
    this.gameOverModal.classList.remove("visible");
  }

  onPlayPauseClick(callback) {
    this.playPauseButton.addEventListener("click", callback);
  }

  onRestartClick(callback) {
    this.restartButton.addEventListener("click", callback);
    this.modalRestartButton.addEventListener("click", callback);
  }

  onClearClick(callback) {
    this.clearButton.addEventListener("click", callback);
  }

  onEntitySelect(callback) {
    this.entityOptions.forEach((option) => {
      option.addEventListener("click", () => {
        const entityType = parseInt(option.dataset.entity);
        callback(entityType);
      });
    });
  }
}
