<template>
  <g>
    <text v-if="state == 9"
          :x="x * 30 + 15" 
          :y="y * 30 + 15" 
          text-anchor="middle" 
          dominant-baseline="central">
      M
    </text>
    <text v-if="1 <= state && state <= 8"
          :x="x * 30 + 15" 
          :y="y * 30 + 15" 
          text-anchor="middle" 
          dominant-baseline="central">
      {{ state }}
    </text>
    <rect class="cell" :class="{ concealed: !opened }"
          :x="x * 30 + 1"
          :y="y * 30 + 1"
          :width="30 - 2"
          :height="30 - 2"
          @click="$emit('open', x, y)">
    </rect>
  </g>
</template>

<script>
  export default {
    name: 'Cell',
    props: ['x', 'y', 'state', 'opened']
  }
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
  .cell {
    fill-opacity: 0.0;
    stroke: #757575;
    stroke-width: 1px;
  }

  .concealed {
    fill: #EEEEEE;
    fill-opacity: 1.0;
  }
</style>
