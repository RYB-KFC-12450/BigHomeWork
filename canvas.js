var canvas = document.getElementById("mycanvas");
if (canvas.getContext) {
	var ctx = canvas.getContext("2d");
}
var posX = 0;
var posY = 0;
var vx = 4,
	vy = 0,
	grativity = 9.8 / 10000;
var v,fx,fy,fraction,cos,sin;
setInterval(function() {
	ctx.fillStyle = "black";
	ctx.fillRect(0, 0, canvas.width, canvas.height);
	posX += vx;
	posY += vy;
	if (posY + vy > canvas.height || posY + vy < 0) {
		vy *= -0.99;
	}
	if (posX + vx > canvas.width || posX + vx < 0) {
		vx *= -0.99;
	}
	v = Math.sqrt(vx * vx + vy * vy);
	sin = Math.abs(vy / v);
	cos = Math.abs(vx / v);
	fraction = -0.5 * v * v / 0.1 / 10000;
	fx = fraction * cos;
	fy = fraction * sin;
	if (posY != canvas.height) {
		if (vx > 0) {
			vx += fx;
		}
		if (vx < 0) {
			vx -= fx;
		}
	}
	if (vy == 0) {
		if (vx > 0) {
			vx -= 0.6 * 9.8 / 10000;
		}
		if (vx < 0) {
			vx += 0.6 * 9.8 / 10000;
		}
	}
	vy += grativity;
	if (vy > 0) {
		vy += fy;
	}
	if (vy < 0) {
		vy -= fy;
	}
	if (posY + vy > canvas.height) {
		vy = 0;
	}
	ctx.beginPath();
	ctx.fillStyle = "blue";
	ctx.arc(posX, posY, 5, 0, Math.PI * 2, true);
	ctx.closePath();
	ctx.fill()
	ctx.beginPath();
	ctx.moveTo( 0,posY);
	ctx.lineTo(canvas.width,posY);
	ctx.linewidth = 2.0;
	ctx.strokeStyle = "red";
	ctx.stroke();
	ctx.moveTo(posX, 0);
	ctx.lineTo(posX,canvas.height);
	ctx.linewidth = 2.0;
	ctx.strokeStyle = "red";
	ctx.stroke();
}, 10);
setInterval(function(){
	document.getElementById("p1").innerHTML = "X:" + posX.toFixed(2);
	document.getElementById("p2").innerHTML = "Y:" + posY.toFixed(2);
	document.getElementById("p3").innerHTML = "Vx:" + vx.toFixed(2);
	document.getElementById("p4").innerHTML = "Vy:" + vy.toFixed(2);
	document.getElementById("p5").innerHTML = "V:" + v.toFixed(2);
}, 250);