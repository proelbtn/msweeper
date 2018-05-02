// The Vue build version to load with the `import` command
// (runtime-only or standalone) has been set in webpack.base.conf with an alias.
import Vue from 'vue'
import App from './App'

Vue.config.productionTip = false
Vue.config.performance = true;

// ref: https://stackoverflow.com/questions/610406/javascript-equivalent-to-printf-string-format
// First, checks if it isn't implemented yet.
if (!String.prototype.format) {
  String.prototype.format = function() {
    var args = arguments;
    return this.replace(/{(\d+)}/g, function(match, number) { 
      return typeof args[number] != 'undefined'
        ? args[number]
        : match
      ;
    });
  };
}

function getParams() {
  let obj = {};
  const h = document.location.href;
  for (let v of h.substr(h.search(/\?/) + 1).split('&')) {
    const key = v.substr(0, v.search('='));
    const val = v.substr(v.search('=') + 1);
    obj[key] = val;
  }
  return obj;
}

function test() {
  const params = getParams();
  const width = params['w'] || 8;
  const height = params['h'] || 8;
  const bnum = params['n'] || 8;
  return '<App w="{0}" h="{1}" n="{2}" />'.format(width, height, bnum);
}

/* eslint-disable no-new */
new Vue({
  el: '#app',
  components: {App},
  template: test()
});