const GRID_SIZE = 25;
const ENTITY_FOX = 1;
const ENTITY_RABBIT = 2;
const ENTITY_GRASS = 3;

export class Grid {
  constructor(gridElement) {
    this.gridElement = gridElement;
    this.cells = [];
    this.createCells();
  }

  createCells() {
    for (let i = 0; i < GRID_SIZE * GRID_SIZE; i++) {
      const cell = document.createElement("div");
      cell.className = "cell";
      this.gridElement.appendChild(cell);
      this.cells.push(cell);
    }
  }

  render() {
    for (let x = 0; x < GRID_SIZE; x++) {
      for (let y = 0; y < GRID_SIZE; y++) {
        const cellIndex = x * GRID_SIZE + y;
        const cell = this.cells[cellIndex];
        const entityType = window.Module._getEntityAt(x, y);

        cell.innerHTML = "";
        cell.className = "cell";

        switch (entityType) {
          case ENTITY_FOX:
            cell.innerHTML =
              '<img src="assets/fox.png" alt="Fox" class="entity-sprite">';
            cell.classList.add("fox");
            break;
          case ENTITY_RABBIT:
            cell.innerHTML =
              '<img src="assets/rabbit.png" alt="Rabbit" class="entity-sprite">';
            cell.classList.add("rabbit");
            break;
          case ENTITY_GRASS:
            cell.innerHTML =
              '<img src="assets/grass.png" alt="Grass" class="entity-sprite">';
            cell.classList.add("grass");
            break;
        }
      }
    }
  }

  getCellCoordinates(cell) {
    const cellIndex = this.cells.indexOf(cell);
    if (cellIndex === -1) return null;

    const x = Math.floor(cellIndex / GRID_SIZE);
    const y = cellIndex % GRID_SIZE;
    return { x, y };
  }

  onCellClick(callback) {
    this.gridElement.addEventListener("click", (event) => {
      const cell = event.target.closest(".cell");

      if (!cell || !this.gridElement.contains(cell)) return;

      const coords = this.getCellCoordinates(cell);
      if (coords) {
        callback(coords.x, coords.y);
      }
    });
  }
}
