import { GameState } from "./state.js";
import { Timer } from "./timer.js";
import { Grid } from "./grid.js";
import { UI } from "./ui.js";
import { GRID_SIZE } from "./grid.js";

const ENTITY_FOX = 1;
const ENTITY_RABBIT = 2;
const ENTITY_GRASS = 3;

const ENTITY_NAMES = {
  [ENTITY_FOX]: "Raposas",
  [ENTITY_RABBIT]: "Coelhos",
  [ENTITY_GRASS]: "Grama",
};

class Game {
  constructor() {
    this.timer = new Timer(document.getElementById("timer-value"));
    this.grid = new Grid(document.getElementById("grid"));
    this.ui = new UI();
    this.gameInterval = null;
    this.isWasmReady = false;

    this.setupEventHandlers();
  }

  initialize() {
    try {
      if (typeof window.Module._initializeEcosystem !== "function") {
        console.error("WASM module not properly initialized");
        this.showWasmError();
        return;
      }

      window.Module._initializeEcosystem();
      this.isWasmReady = true;
      this.grid.render();
      this.updateStartButtonState();
    } catch (error) {
      console.error("Failed to initialize ecosystem:", error);
      this.showWasmError();
    }
  }

  showWasmError() {
    const gridElement = document.getElementById("grid");
    gridElement.innerHTML =
      '<div style="grid-column: 1/-1; display: flex; align-items: center; justify-content: center; text-align: center; padding: 20px; color: var(--color-forest-dark);">Erro ao carregar simulador.<br>Tente recarregar a página.</div>';
    this.ui.disableStartButton();
  }

  setupEventHandlers() {
    this.ui.onPlayPauseClick(() => this.handlePlayPause());
    this.ui.onRestartClick(() => this.handleRestart());
    this.ui.onClearClick(() => this.handleClear());
    this.ui.onEntitySelect((entityType) => this.handleEntitySelect(entityType));
    this.grid.onCellClick((x, y) => this.handleCellClick(x, y));
  }

  hasAnyEntities() {
    if (!this.isWasmReady) {
      return false;
    }
    const foxCount = window.Module._countEntityType(ENTITY_FOX);
    const rabbitCount = window.Module._countEntityType(ENTITY_RABBIT);
    const grassCount = window.Module._countEntityType(ENTITY_GRASS);
    return foxCount > 0 || rabbitCount > 0 || grassCount > 0;
  }

  updateStartButtonState() {
    if (!this.isWasmReady) {
      this.ui.disableStartButton();
      return;
    }

    if (GameState.isIdle() && !this.hasAnyEntities()) {
      this.ui.disableStartButton();
    } else {
      this.ui.enableStartButton();
    }
  }

  handlePlayPause() {
    if (GameState.isIdle()) {
      if (!this.hasAnyEntities()) {
        return;
      }
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
    if (!this.isWasmReady) return;

    this.stopGameLoop();
    this.timer.reset();
    GameState.setIdle();
    GameState.selectedEntity = null;
    this.ui.setPlayPauseText("Iniciar");
    this.ui.deselectAllEntities();
    this.ui.enableEntitySelection();
    this.ui.hideGameOver();

    try {
      window.Module._initializeEcosystem();
      this.grid.render();
      this.updateStartButtonState();
    } catch (error) {
      console.error("Failed to restart ecosystem:", error);
      this.showWasmError();
    }
  }

  handleClear() {
    this.stopGameLoop();
    this.timer.reset();
    GameState.setIdle();
    GameState.selectedEntity = null;
    this.ui.setPlayPauseText("Iniciar");
    this.ui.deselectAllEntities();
    this.ui.enableEntitySelection();
    this.ui.hideGameOver();

    for (let x = 0; x < GRID_SIZE; x++) {
      for (let y = 0; y < GRID_SIZE; y++) {
        window.Module._removeEntity(x, y);
      }
    }
    this.grid.render();
    this.updateStartButtonState();
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
    this.updateStartButtonState();
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
    const extinctEntityType = window.Module._checkExtinction();

    if (extinctEntityType !== 0) {
      this.gameOver(ENTITY_NAMES[extinctEntityType]);
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

window.Module = window.Module || {};
let gameInstance = null;

const originalOnRuntimeInitialized = window.Module.onRuntimeInitialized;
window.Module.onRuntimeInitialized = function () {
  console.log("WASM runtime initialized");
  if (originalOnRuntimeInitialized) {
    originalOnRuntimeInitialized();
  }
  if (gameInstance) {
    gameInstance.initialize();
  }
};

window.addEventListener("load", () => {
  gameInstance = new Game();

  if (window.Module.calledRun) {
    console.log("WASM already initialized on load");
    gameInstance.initialize();
  } else {
    console.log("Waiting for WASM to initialize...");
  }

  setTimeout(() => {
    if (gameInstance && !gameInstance.isWasmReady) {
      console.error("WASM failed to initialize within timeout");
      gameInstance.showWasmError();
    }
  }, 10000);
});
