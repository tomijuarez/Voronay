function Drawer() {};

Drawer.prototype.setCanvas= function(canvas) {
    this.canvas = canvas;
};

Drawer.prototype.getContext = function() {
    return this.canvas.getContext("2d");
}

Drawer.prototype.repaint = function() {
    this.canvas.requestPaint();
}

Drawer.prototype.drawTriangle = function(x1, y1, x2, y2, x3, y3) {
    var context = this.getContext();

    context.beginPath();
    context.moveTo(x1, y1);
    context.lineTo(x2, y2);
    context.lineTo(y3, y3);
    context.closePath();

    // the outline
    context.lineWidth = 5;
    context.strokeStyle = '#F62459';
    context.stroke();

    // the fill color
    context.fillStyle = "#C5EFF7";
    context.fill();
}

var Drawer = new Drawer();
