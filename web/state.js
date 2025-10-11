const GameStateEnum = {
  IDLE: 0,
  RUNNING: 1,
  PAUSED: 2,
  GAMEOVER: 3
};

export const GameState = {
  selectedEntity: null,

  isIdle() {
    return window.Module._getGameState() === GameStateEnum.IDLE;
  },

  isPaused() {
    return window.Module._getGameState() === GameStateEnum.PAUSED;
  },

  isRunning() {
    return window.Module._getGameState() === GameStateEnum.RUNNING;
  },

  isGameOver() {
    return window.Module._getGameState() === GameStateEnum.GAMEOVER;
  },

  canSelectEntity() {
    return this.isIdle();
  },

  canPlaceEntity() {
    return window.Module._canPlaceEntity();
  },

  setIdle() {
    window.Module._setGameState(GameStateEnum.IDLE);
  },

  setPaused() {
    window.Module._setGameState(GameStateEnum.PAUSED);
  },

  setRunning() {
    window.Module._setGameState(GameStateEnum.RUNNING);
  },

  setGameOver() {
    window.Module._setGameState(GameStateEnum.GAMEOVER);
  }
};
