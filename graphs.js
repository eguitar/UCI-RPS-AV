function getTimeValue() {
    var dateBuffer = new Date();
    var Time = dateBuffer.getTime();
    return Time;
  }

  function getRandomValue() {
    var randomValue = Math.random() * 100;
    return randomValue;
  }

  function updateGraph() {
    var newLineChartData = [{time: getTimeValue(), y:getRandomValue()}];
  
    /* Wrong: don't use the full configuration for an update.
    var newBarChartData = [{
      label: "Series 1",
      values: [{
        time: getTimeValue(),
        y: getRandomValue()
      }]
    }, ];
    */
    myChart.push(newLineChartData);
  }
  
  
  var lineChartInstance = new Epoch.Time.Line({data: lineChartData, range: {left: 'range-l'}});