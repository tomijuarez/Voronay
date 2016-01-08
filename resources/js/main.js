function Drawer() {};

Drawer.prototype.zoomFactor = 0.5;
Drawer.prototype.zoomTransformFactor = 1;
Drawer.prototype.translateFactor = 10;

Drawer.prototype.translateNumber = function(number){
    var result = (number/this.zoomTransformFactor);
    return result;
};

Drawer.prototype.translateNumberInv = function(number){
    var result = (number*this.zoomTransformFactor);
    return result;
};

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

    context.lineWidth = 1;
    context.strokeStyle = '#F62459';
    context.stroke();

}

Drawer.prototype.drawCircle = function(x,y,r) {
    var context = this.getContext();
    context.beginPath();
    context.arc(x, y, r, 0, 2 * Math.PI);
    context.closePath();

    context.strokeStyle = "#00B16A";
    context.stroke();
}

Drawer.prototype.drawPaintedCircle = function(x,y,r) {
    var context = this.getContext();
    context.beginPath();
    context.arc(x, y, r, 0, 2 * Math.PI);
    context.closePath();

    context.fillStyle="#794044";
    context.fill();

    context.strokeStyle = "#794044";
    context.stroke();
}

Drawer.prototype.drawLine = function(x1,y1,x2,y2) {
    var context = this.getContext();

    context.beginPath();
    context.moveTo(x1,y1);
    context.lineTo(x2,y2);

    context.closePath();

    context.lineWidth = 1;
    context.strokeStyle = "#0287D0";
    context.stroke();
}

Drawer.prototype.drawPoint = function(x,y) {
    var context = this.getContext();
    context.fillStyle = "#1BA39C";

    context.fillRect(x-2,y-2,5,5);
}

Drawer.prototype.zoomIn = function() {
    var context = this.getContext();
    this.zoomTransformFactor = this.zoomTransformFactor - this.zoomFactor;
}

Drawer.prototype.zoomOut = function() {
    var context = this.getContext();
    this.zoomTransformFactor = this.zoomTransformFactor + this.zoomFactor;
}

Drawer.prototype.up = function() {
    var context = this.getContext();

    this.clear();

    context.translate(0,this.translateFactor);
}

Drawer.prototype.down = function() {
    var context = this.getContext();

    this.clear();

    context.translate(0,-this.translateFactor);
}

Drawer.prototype.left = function() {
    var context = this.getContext();

    this.clear();

    context.translate(-this.translateFactor,0);
}

Drawer.prototype.right = function() {
    var context = this.getContext();

    this.clear();

    context.translate(this.translateFactor,0);
}

var Drawer = new Drawer();
