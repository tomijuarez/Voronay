function Drawer() {};

Drawer.prototype.zoomFactor = 0.1;
Drawer.prototype.zoom = 1;
Drawer.prototype.translateFactor = 10;

Drawer.prototype.setCanvas = function(canvas) {
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

Drawer.prototype.applyAxisTransformation = function() {
    var context = this.getContext();
    context.transform(1, 0, 0, -1, 0, this.canvas.height);
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

}

Drawer.prototype.drawPoint = function(x,y) {
    var context = this.getContext();
    context.fillStyle = "#1BA39C";

    context.fillRect(x-2,y-2,5,5);
}

Drawer.prototype.zoomIn = function() {
    var context = this.getContext();
    this.zoom = this.zoom + this.zoomFactor;

    this.clear();
    context.scale(this.zoom, this.zoom);
    this.applyAxisTransformation();
}

Drawer.prototype.zoomOut = function() {
    var context = this.getContext();
    this.zoom = this.zoom - this.zoomFactor;

    this.clear();
    context.scale(this.zoom, this.zoom);
    this.applyAxisTransformation();
}

Drawer.prototype.up = function() {
    var context = this.getContext();

    this.clear();
    this.applyAxisTransformation();

    context.translate(0,this.translateFactor);
}

Drawer.prototype.down = function() {
    var context = this.getContext();

    this.clear();
    this.applyAxisTransformation();

    context.translate(0,-this.translateFactor);
}

Drawer.prototype.left = function() {
    var context = this.getContext();

    this.clear();
    this.applyAxisTransformation();

    context.translate(-this.translateFactor,0);
}

Drawer.prototype.right = function() {
    var context = this.getContext();

    this.clear();
    this.applyAxisTransformation();

    context.translate(this.translateFactor,0);
}

var Drawer = new Drawer();
