<template>
  <svg id="app" :width="width * 30" :height="height * 30">
    <g v-for="y in range(height)">
      <g v-for="x in range(width)">
        <Cell :x="x"
              :y="y"
              :state="getState(x, y)"
              :opened="opened[y * width + x]"
              @open="open"
        />
      </g>
    </g>
  </svg>
</template>

<script>
  import Cell from './components/Cell';

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

  export default {
    name: 'App',
    props: ['width', 'height', 'bnum'],
    components: {
      Cell
    },
    methods: {
      range(n) {
        let t = [];
        for (let i = 0; i < n; i++) t[i] = i;
        return t;
      },

      getState(x, y) {
        if (this.bomb[y * this.width + x]) return 9;

        let count = 0;
        for (let dy = -1; dy < 2; dy++) {
          for (let dx = -1; dx < 2; dx++) {
            if (!dx && !dy) continue;
            const nx = x + dx, ny = y + dy;
            if (is_range(nx, ny, this.width, this.height)) {
              if (this.bomb[ny * this.width + nx]) count++;
            }
          }
        }
        return count;
      },

      open(x, y) {
        this.opened.splice(y * this.height + x, 1, true);
        if (this.getState(x, y) != 0) return; 
        for (let dy = -1; dy < 2; dy++) {
          for (let dx = -1; dx < 2; dx++) {
            if (!dx && !dy) continue;
            const nx = x + dx, ny = y + dy;
            if (is_range(nx, ny, this.width, this.height)) {
              if (!this.opened[ny * this.width + nx]) this.open(nx, ny);
            }
          }
        }
      }
    },
    data() {
      let bomb = [], opened = [];
      for (let pos = 0; pos < this.width * this.height; pos++) {
        opened[pos] = false;
        bomb[pos] = pos < this.bnum;
      }
      return {
        bomb: shuffleArray(bomb),
        opened: opened
      }
    }
  }
</script>

<style>
  #app {
    background: #BDBDBD;
  }
</style>
