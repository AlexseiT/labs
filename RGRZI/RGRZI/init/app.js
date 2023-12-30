

function initValues()
{
  eel.GetValues()(function(values){                       
    const data = new gridjs.Grid({
      data: values[2]
    }).render(document.getElementById("wrapper"));
    let g = new Dracula.Graph();
    i = 1;
    values[2].forEach((arr) => {
      arr.forEach((element,index) => {
        if (element == 1) g.addEdge(i,index+1);
      })
      i += 1;
    });

    let layouter = new Dracula.Layout.Spring(g);
    layouter.layout();
    let renderer = new Dracula.Renderer.Raphael(document.getElementById('canvas'), g, 800, 400);
    renderer.draw();

    // const N = document.querySelector(".classN");
    // const M = document.querySelector(".classM");
    
    // N.textContent = values[0].toString();
    // M.textContent = values[1].toString();
  }) 
}
function initGraph()
{
  const button = document.querySelector(".input__button");
  button.addEventListener("click", () => {
    eel.HamCycle()(function(values){  
      console.log(values);
      let g = new Dracula.Graph();
      i = 1;
      values[0].forEach((arr) => {
        arr.forEach((element,index) => {
          if (element == 1) g.addEdge(i,index+1);
        })
        i += 1;
      });
  
      let layouter = new Dracula.Layout.Spring(g);
      layouter.layout();
      let renderer = new Dracula.Renderer.Raphael(document.getElementById('canvasG'), g, 800, 400);
      renderer.draw();

      g = new Dracula.Graph();
      i = 1;
      values[1].forEach((arr) => {
        arr.forEach((element,index) => {
          if (element == 1) g.addEdge(i,index+1);
        })
        i += 1;
      });
  
      layouter = new Dracula.Layout.Spring(g);
      layouter.layout();
      renderer = new Dracula.Renderer.Raphael(document.getElementById('canvasH'), g, 800, 400);
      renderer.draw();
    }) 


  });
}
document.addEventListener('DOMContentLoaded', (event) => {
  initGraph();
  initValues();

})