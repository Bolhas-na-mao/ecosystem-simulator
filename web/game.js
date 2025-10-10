import { GameState } from "./state.js";
import { Timer } from "./timer.js";
import { Grid } from "./grid.js";
import { UI } from "./ui.js";

class Game {
  constructor() {
    this.timer = new Timer(document.getElementById("timer-value"));
    this.grid = new Grid(document.getElementById("grid"));
    this.ui = new UI();
    this.gameInterval = null;

    this.setupEventHandlers();
    this.initialize();
  }

  initialize() {
    window.Module._initializeEcosystem();
    this.grid.render();
  }

  setupEventHandlers() {
    this.ui.onPlayPauseClick(() => this.handlePlayPause());
    this.ui.onRestartClick(() => this.handleRestart());
    this.ui.onClearClick(() => this.handleClear());
    this.ui.onEntitySelect((entityType) => this.handleEntitySelect(entityType));
    this.grid.onCellClick((x, y) => this.handleCellClick(x, y));
  }

  handlePlayPause() {
    if (GameState.isIdle()) {
      this.startGame();
    } else if (GameState.isRunning()) {
      this.pauseGame();
    } else if (GameState.isPaused()) {
      this.resumeGame();
    }
  }

  startGame() {
    GameState.setRunning();
    this.timer.reset();
    this.timer.start();
    this.ui.setPlayPauseText("Pausar");
    this.ui.disableEntitySelection();
    this.grid.render();
    this.startGameLoop();
  }

  pauseGame() {
    GameState.setPaused();
    this.timer.pause();
    this.ui.setPlayPauseText("Retomar");
    this.ui.disableEntitySelection();
    this.stopGameLoop();
  }

  resumeGame() {
    GameState.setRunning();
    this.timer.start();
    this.ui.setPlayPauseText("Pausar");
    this.ui.disableEntitySelection();
    this.startGameLoop();
  }

  handleRestart() {
    this.stopGameLoop();
    this.timer.reset();
    GameState.setIdle();
    GameState.selectedEntity = null;
    this.ui.setPlayPauseText("Iniciar");
    this.ui.deselectAllEntities();
    this.ui.enableEntitySelection();
    this.ui.hideGameOver();
    window.Module._initializeEcosystem();
    this.grid.render();
  }

  handleClear() {
    if (!GameState.isIdle()) {
      return;
    }

    for (let x = 0; x < 25; x++) {
      for (let y = 0; y < 25; y++) {
        window.Module._removeEntity(x, y);
      }
    }
    this.grid.render();
  }

  handleEntitySelect(entityType) {
    if (!GameState.canSelectEntity()) {
      return;
    }

    if (GameState.selectedEntity === entityType) {
      GameState.selectedEntity = null;
      this.ui.deselectAllEntities();
    } else {
      GameState.selectedEntity = entityType;
      this.ui.selectEntity(entityType);
    }
  }

  handleCellClick(x, y) {
    if (!GameState.canPlaceEntity()) {
      return;
    }

    const existingEntity = window.Module._getEntityAt(x, y);

    if (existingEntity !== 0) {
      if (GameState.selectedEntity) {
        window.Module._replaceEntity(x, y, GameState.selectedEntity);
      } else {
        window.Module._removeEntity(x, y);
      }
    } else if (GameState.selectedEntity) {
      window.Module._placeEntity(x, y, GameState.selectedEntity);
    }

    this.grid.render();
  }

  startGameLoop() {
    this.gameInterval = setInterval(() => {
      window.Module._tickEcosystem();
      this.grid.render();
      this.checkExtinction();
    }, 1000);
  }

  stopGameLoop() {
    if (this.gameInterval) {
      clearInterval(this.gameInterval);
      this.gameInterval = null;
    }
  }

  checkExtinction() {
    const foxCount = window.Module._countEntityType(1);
    const rabbitCount = window.Module._countEntityType(2);
    const grassCount = window.Module._countEntityType(3);

    let extinctEntity = null;
    if (foxCount === 0) extinctEntity = "Raposas";
    else if (rabbitCount === 0) extinctEntity = "Coelhos";
    else if (grassCount === 0) extinctEntity = "Grama";

    if (extinctEntity) {
      this.gameOver(extinctEntity);
    }
  }

  gameOver(extinctEntity) {
    GameState.setGameOver();
    this.stopGameLoop();
    this.timer.pause();
    this.ui.showGameOver(extinctEntity);
    this.ui.setPlayPauseText("Iniciar");
  }
}

window.addEventListener("load", () => {
  setTimeout(() => {
    if (typeof window.Module !== "undefined" && window.Module._initializeEcosystem) {
      new Game();
    }
  }, 100);
});
