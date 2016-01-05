function Drawer() {};

Drawer.prototype.zoomFactor = 0.1;
Drawer.prototype.zoom = 1;

Drawer.prototype.setCanvas= function(canvas) {
    this.canvas = canvas;
};

Drawer.prototype.getContext = function() {
    return this.canvas.getContext("2d");
}

Drawer.prototype.repaint = function() {
    this.canvas.requestPaint();
}

Drawer.prototype.clear = function() {
    var context = this.getContext();
    context.clearRect(0, 0, this.canvas.width, this.canvas.height);
}

Drawer.prototype.drawTriangle = function(x1, y1, x2, y2, x3, y3) {
    var context = this.getContext();

    context.beginPath();
    context.moveTo(x1, y1);
    context.lineTo(x2, y2);
    context.lineTo(x3, y3);
    context.closePath();

    // the outline
    context.lineWidth = 1;
    context.strokeStyle = '#F62459';
    context.stroke();

    // the fill color
    context.fillStyle = "#C5EFF7";
    context.fill();
}

Drawer.prototype.drawPoint = function(x,y) {
    var context = this.getContext();
    context.strokeRect(x,y,1,1);
}

Drawer.prototype.zoomIn = function() {
    var context = this.getContext();
    this.zoom = this.zoom + this.zoomFactor;
    console.log("--------------------" + this.zoom);
    context.scale(this.zoom, this.zoom);
}

Drawer.prototype.zoomOut = function() {
    var context = this.getContext();
    this.zoom = this.zoom - this.zoomFactor;
    console.log(this.zoom);
    context.scale(this.zoom, this.zoom);
}

var Drawer = new Drawer();
