export const GameState = {
  current: "idle",
  selectedEntity: null,

  isIdle() {
    return this.current === "idle";
  },

  isPaused() {
    return this.current === "paused";
  },

  isRunning() {
    return this.current === "running";
  },

  isGameOver() {
    return this.current === "gameover";
  },

  canSelectEntity() {
    return this.isIdle();
  },

  canPlaceEntity() {
    return this.isIdle();
  },

  setIdle() {
    this.current = "idle";
  },

  setPaused() {
    this.current = "paused";
  },

  setRunning() {
    this.current = "running";
  },

  setGameOver() {
    this.current = "gameover";
  }
};
