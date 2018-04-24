<template>
  <svg id="app" width="240" height="240">
    <g v-for="y in range(8)">
      <g v-for="x in range(8)">
        <Cell :x="x"
              :y="y"
              :state="getState(x, y)"
              :opened="opened[y * 8 + x]"
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

  export default {
    name: 'App',
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
        let count = 0;
        for (let dy = -1; dy < 2; dy++) {
          for (let dx = -1; dx < 2; dx++) {
            if (!dx && !dy) continue;
            const nx = x + dx, ny = y + dy;
            if (0 <= nx && nx < 8 && 0 <= ny && ny < 8 && this.bomb[ny * 8 + nx]) count++;
          }
        }
      },
      open(x, y) {
        this.opened.splice(y * 8 + x, 1, true);
      }
    },
    data() {
      let bomb = [], opened = [];
      for (let pos = 0; pos < 64; pos++) {
        opened[pos] = false;
        bomb[pos] = pos < 10;
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
