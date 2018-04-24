<template>
  <g>
    <rect class="cell" :class="{ concealed: !opened }"
          :x="x * 30 + 1"
          :y="y * 30 + 1"
          width="28"
          height="28"
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
