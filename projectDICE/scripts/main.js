class Randomizer
{
    constructor() {}
    GetRandom(numberMin,numberMax)
    {
        return Math.floor(Math.random() * (numberMax - numberMin)) + numberMin;
    }
    Visualize() {}
    CheckCount() {}
}
class Dice extends Randomizer
{
    constructor()
    {
        super();
        this.numberRand = super.GetRandom(1, 6);
        this.src = "assets/images/dice/" + this.numberRand + ".png";
        this.image = new Image();
        this.image.src = this.src;
    }
    CheckCount()
    {
        return document.getElementById("dicePlace").getElementsByTagName("img").length;
    }
    Visualize()
    {
        console.log(this.CheckCount());
        if (this.CheckCount() > 49) document.getElementById('dicePlace').innerHTML = "";
        document.getElementById('dicePlace').appendChild(this.image);
    }
}
class Card extends Randomizer
{
    constructor() {}
    CheckCount() {}
    Visualize() {}
}
function OnClickButtonRoll()
{
    render = new Dice();
    render.Visualize();
}