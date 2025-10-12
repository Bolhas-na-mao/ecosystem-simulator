export const GRID_SIZE = 25;
const ENTITY_FOX = 1;
const ENTITY_RABBIT = 2;
const ENTITY_GRASS = 3;

export class Grid {
  constructor(gridElement) {
    this.gridElement = gridElement;
    this.cells = [];
    this.isMouseDown = false;

    this._onMouseUp = this._handleMouseUp.bind(this);
    this._onDragStart = this._handleDragStart.bind(this);

    this.createCells();

    document.addEventListener("mouseup", this._onMouseUp);
    this.gridElement.addEventListener("dragstart", this._onDragStart);
  }

  _handleMouseUp(event) {
    if (event.button === 0) {
      this.isMouseDown = false;
    }
  }

  _handleDragStart(event) {
    event.preventDefault();
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
    if (this._onMouseDown) {
      this.gridElement.removeEventListener("mousedown", this._onMouseDown);
    }
    if (this._onMouseOver) {
      this.gridElement.removeEventListener("mouseover", this._onMouseOver);
    }

    this._onMouseDown = (event) => {
      if (event.button !== 0) return;

      this.isMouseDown = true;
      const cell = event.target.closest(".cell");

      if (!cell || !this.gridElement.contains(cell)) return;

      const coords = this.getCellCoordinates(cell);
      if (coords) {
        callback(coords.x, coords.y);
      }
    };

    this._onMouseOver = (event) => {
      if (!this.isMouseDown) return;

      const cell = event.target.closest(".cell");

      if (!cell || !this.gridElement.contains(cell)) return;

      const coords = this.getCellCoordinates(cell);
      if (coords) {
        callback(coords.x, coords.y);
      }
    };

    this.gridElement.addEventListener("mousedown", this._onMouseDown);
    this.gridElement.addEventListener("mouseover", this._onMouseOver);
  }

  destroy() {
    document.removeEventListener("mouseup", this._onMouseUp);
    this.gridElement.removeEventListener("dragstart", this._onDragStart);

    if (this._onMouseDown) {
      this.gridElement.removeEventListener("mousedown", this._onMouseDown);
    }
    if (this._onMouseOver) {
      this.gridElement.removeEventListener("mouseover", this._onMouseOver);
    }
  }
}
