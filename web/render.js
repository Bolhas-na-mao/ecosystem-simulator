const grid = document.getElementById("grid");
const startButton = document.getElementById("start-button");

let gameInterval = null;
let isGameRunning = false;

for (let i = 0; i < 625; i++) {
  const cell = document.createElement("div");
  cell.className = "cell";
  grid.appendChild(cell);
}

window.addEventListener("load", () => {
  setTimeout(() => {
    if (typeof Module !== "undefined" && Module._initializeEcosystem) {
      startButton.addEventListener("click", startGame);
    }
  }, 100);
});

function startGame() {
  if (isGameRunning) return;

  Module._initializeEcosystem();

  isGameRunning = true;
  startButton.textContent = "Em execução...";
  startButton.disabled = true;

  renderGrid();

  gameInterval = setInterval(() => {
    Module._tickEcosystem();
    renderGrid();
  }, 1000);
}

function renderGrid() {
  const cells = grid.children;

  for (let x = 0; x < 25; x++) {
    for (let y = 0; y < 25; y++) {
      const cellIndex = x * 25 + y;
      const cell = cells[cellIndex];

      const entityType = Module._getEntityAt(x, y);

      cell.textContent = "";

      switch (entityType) {
        case 1:
          cell.textContent = "F";
          break;
        case 2:
          cell.textContent = "R";
          break;
        case 3:
          cell.textContent = "G";
          break;
        default:
          cell.textContent = "";
          break;
      }
    }
  }
}
