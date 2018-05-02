<template>
  <svg id="app" :width="w * 30" :height="h * 30">
    <g v-for="y in range(h)">
      <g v-for="x in range(w)">
        <Cell :x="x"
              :y="y"
              :state="cells[y * w + x]"
              :opened="opened[y * w + x]"
              @open="open"
        />
      </g>
    </g>
    <rect v-if="getGameState() != 0" class="vail-rect"
          x="0"
          y="0"
          :width="w * 30"
          :height="h * 30" />
    <text class="result result-clear" v-if="getGameState() == 1"
          :x="w * 30 / 2" 
          :y="h * 30 / 2" 
          text-anchor="middle" 
          dominant-baseline="central">
      GAME CLEAR!
    </text>
    <text class="result result-over" v-if="getGameState() == 2"
          :x="w * 30 / 2" 
          :y="h * 30 / 2" 
          text-anchor="middle" 
          dominant-baseline="central">
      GAME OVER...
    </text>
    <text class="result result-error" v-if="getGameState() == 3"
          :x="w * 30 / 2" 
          :y="h * 30 / 2" 
          text-anchor="middle" 
          dominant-baseline="central">
      ERROR!
    </text>
  </svg>
</template>

<script>
  import Cell from './components/Cell';

  const GAME_IS_STILL_CONTINUED = 0;
  const GAME_IS_CLEAR = 1;
  const GAME_IS_OVER = 2;
  const GAME_IS_ERROR = 3;

  function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
      let j = Math.floor(Math.random() * (i + 1)), t;
      t = array[i];
      array[i] = array[j];
      array[j] = t;
    }
    return array;
  }

  function is_range(x, y, w, h) {
    return 0 <= x && x < w && 0 <= y && y < h;
  }

  function coord2pos(x, y, w, h) {
    return y * w + x;
  }

  export default {
    name: 'App',
    props: ['w', 'h', 'n'],
    components: {
      Cell
    },
    methods: {
      range(n) {
        let t = [];
        for (let i = 0; i < n; i++) t[i] = i;
        return t;
      },

      getGameState() {
        if (!this.dirty) return pstate;

        if (this.n < 0 || this.w * this.h < this.n) return GAME_IS_ERROR;

        let f = false;
        for (let pos = 0; pos < this.w * this.h; pos++) {
          if (this.opened[pos] && this.bomb[pos]) return GAME_IS_OVER;
          if (!this.opened[pos] && !this.bomb[pos]) f = true;
        }
        return f ? GAME_IS_STILL_CONTINUED : GAME_IS_CLEAR;
      },

      open(x, y) {
        this.dirty = true;

        this.opened.splice(y * this.w + x, 1, true);
        if (this.cells[y * this.w + x] != 0) return;

        for (let dy = -1; dy < 2; dy++) {
          for (let dx = -1; dx < 2; dx++) {
            if (!dx && !dy) continue;
            const nx = x + dx, ny = y + dy;
            if (is_range(nx, ny, this.w, this.h)) {
              if (!this.opened[coord2pos(nx, ny, this.w, this.h)]) this.open(nx, ny);
            }
          }
        }
      }
    },

    data() {
      let bomb = [], opened = [], cells = [];

      for (let pos = 0; pos < this.w * this.h; pos++) {
        opened[pos] = false;
        bomb[pos] = pos < this.n;
      }

      bomb = shuffleArray(bomb);

      for (let y = 0; y < this.h; y++) {
        for (let x = 0; x < this.w; x++) {
          let count = 0;
          for (let dy = -1; dy < 2; dy++) {
            for (let dx = -1; dx < 2; dx++) {
              if (!dx && !dy) continue;
              const nx = x + dx, ny = y + dy;
              if (is_range(nx, ny, this.w, this.h) && bomb[coord2pos(nx, ny, this.w, this.h)])
                count++;
            }
          }

          const pos = coord2pos(x, y, this.w, this.h);
          cells[pos] = bomb[pos] ? 9 : count;
        }
      }

      return {
        bomb: bomb,
        opened: opened,
        cells: cells,
        pstate: GAME_IS_STILL_CONTINUED,
        dirty: true
      }
    }
  }
</script>

<style>
  #app {
    background: #BDBDBD;
  }
  
  .vail-rect {
    fill: #FFFFFF;
    fill-opacity: 0.5;
  }

  .result {
    font-size: 20px;
  }

  .result-clear {

  }

  .result-over {

  }

  .result-error {

  }
</style>
