class Canvas {
    constructor() {
        this.getViewport();
        this.getContainer();
        this.initStage();
        this.initShapes();
        this.combineElements();
        this.draw();
        this.initChangeOrderFn();
        this.isLeftOnTop = false;
    }

    getViewport() {
        this.viewport = document.getElementById('viewport');
    }

    getViewportWidth() {
        return this.viewport.getBoundingClientRect().width;
    }

    getViewportHeight() {
        return this.viewport.getBoundingClientRect().height;
    }

    getContainer() {
        this.container = document.getElementById('container');
    }

    initStage() {
        this.stage = new Konva.Stage({
            container: this.container,
            width: this.getViewportWidth(),
            height: this.getViewportHeight(),
        });
    }

    initCircleShape() {
        this.shapes.circle = {};
        this.shapes.circle.main = new Konva.Ellipse({
            x: this.stage.width() / 2,
            y: this.stage.height() / 2,
            width: 60,
            height: 150,
            fill: 'white',
            stroke: 'black',
            strokeWidth: 3,
            rotation: 90,
            draggable: true
        });
        this.shapes.circle.intersection = new Konva.Ellipse({
            x: this.stage.width() / 2,
            y: this.stage.height() / 2,
            width: 60,
            height: 150,
            stroke: 'black',
            strokeWidth: 2,
            rotation: 90,
            dash: [10],
            draggable: true
        });

    }

    initRectangleShape() {
        this.shapes.rectangle = {};
        this.shapes.rectangle.main = new Konva.Line({
            x: this.stage.width() / 2 - 70,
            y: this.stage.height() / 2 + 30,
            points: [0, 0, 0, 150, -300, 150, -150, 0],
            sides: 4,
            width: 200,
            height: 200,
            fill: 'white',
            stroke: 'black',
            strokeWidth: 3,
            draggable: true,
            closed: true,
        });
        this.shapes.rectangle.intersection = new Konva.Line({
            x: this.stage.width() / 2 - 70,
            y: this.stage.height() / 2 + 30,
            points: [0, 0, 0, 150, -300, 150, -150, 0],
            stroke: 'black',
            strokeWidth: 2,
            closed: true,
            dash: [10],
            draggable: true
        });

        this.shapes.rectangle.borderBox = new Konva.Rect({
            x: this.stage.width() / 2 - 450,
            y: this.stage.height() / 2 - 300,
            width: 900,
            height: 550,
            stroke: 'black',
            fill: 'white',
            strokeWidth: 2,
            draggable: true,
        });

        this.shapes.rectangle.borderLine = new Konva.Line({
            x: this.stage.width() / 2 - 450,
            y: this.stage.height() / 2 - 300,
            stroke: 'black',
            points: [0, 0, 900, 0, 900, 550, 0, 550, 0, 0],
            strokeWidth: 2,
            closed: false,
        });
        // const x = this.stage.width() / 2;
        // const y = this.stage.height() / 2;
        /*this.shapes.rectangle.main = new Konva.Line({
            x: this.stage.width() / 2,
            y: this.stage.height() / 2,
            points: [
                x - 50, y - 50,
                x + 50, y - 50,
                x + 75, y,
                x + 75, y + 50,
                x - 75, y + 50,
                x - 75, y,
            ],
            offsetX: 650,
            offsetY: 380,
            width: 500,
            height: 500,
            fill: 'white',
            stroke: 'black',
            strokeWidth: 3,
            draggable: true,
            closed: true,
        });
        this.shapes.rectangle.intersection = new Konva.Line({
            x: this.stage.width() / 2,
            y: this.stage.height() / 2,
            points: [
                x - 50, y - 50,
                x + 50, y - 50,
                x + 75, y,
                x + 75, y + 50,
                x - 75, y + 50,
                x - 75, y,
            ],
            offsetX: 650,
            offsetY: 380,
            width: 500,
            height: 500,
            stroke: 'black',
            strokeWidth: 1,
            dash: [3],
            draggable: true,
            closed: true,
        });*/
    }

    initShapes() {
        this.shapes = {};

        this.initCircleShape();
        this.initRectangleShape();
    }

    clip() {
        this.layers.circle.intersection.clipFunc((context) => {
            context.rect(
                0,
                0,
                this.stage.width(),
                this.stage.height(),
            );
            context.rect(
                this.borderTransform.x(),
                this.borderTransform.y(),
                this.borderTransform.width(),
                this.borderTransform.height()
            );
        });

        this.layers.rectangle.main.clipFunc((context) => {
            context.rect(
                this.borderTransform.x(),
                this.borderTransform.y(),
                this.borderTransform.width(),
                this.borderTransform.height()
            );
        });

        this.layers.circle.main.clipFunc((context) => {
            context.rect(
                this.borderTransform.x(),
                this.borderTransform.y(),
                this.borderTransform.width(),
                this.borderTransform.height()
            );
        });
    }

    combineElements() {
        const layerSettings = {
            x: 0,
            y: 0,
            width: this.stage.width,
            height: this.stage.height,
        };

        this.layers = {};
        this.layers.circle = {};
        this.layers.rectangle = {};

        this.layers.circle.main = new Konva.Layer(layerSettings);
        this.layers.circle.intersection = new Konva.Layer(layerSettings);
        this.layers.circle.main.add(this.shapes.circle.main);
        this.layers.circle.intersection.add(this.shapes.circle.intersection);

        this.layers.rectangle.main = new Konva.Layer(layerSettings);
        this.layers.rectangle.intersection = new Konva.Layer(layerSettings);
        this.layers.rectangle.borderBox = new Konva.Layer(layerSettings);
        this.layers.rectangle.borderLine = new Konva.Layer(layerSettings);

        this.layers.rectangle.main.add(this.shapes.rectangle.main);
        this.layers.rectangle.intersection.add(this.shapes.rectangle.intersection);
        this.layers.rectangle.borderBox.add(this.shapes.rectangle.borderBox);
        this.layers.rectangle.borderLine.add(this.shapes.rectangle.borderLine);


        this.borderTransform = new Konva.Transformer({
            rotateEnabled: false,
            resizeEnabled: false,
            borderEnabled: false,
            boundBoxFunc: (oldBoundBox, newBoundBox) => {
                return newBoundBox;
            },
        });
        this.borderTransform.on('transform ', () => {
            this.stage.batchDraw();
            this.clip();
        });
        this.layers.rectangle.borderBox.add(this.borderTransform);
        this.borderTransform.nodes([this.shapes.rectangle.borderBox]);

        this.stage.add(this.layers.rectangle.borderBox);

        if (this.isLeftOnTop) {
            this.stage.add(this.layers.circle.main);
            this.stage.add(this.layers.rectangle.main);
            this.stage.add(this.layers.rectangle.intersection);
            this.stage.add(this.layers.circle.intersection);
        } else {
            this.stage.add(this.layers.circle.intersection);
            this.stage.add(this.layers.rectangle.main);
            this.stage.add(this.layers.circle.main);
            this.stage.add(this.layers.rectangle.intersection);
        }

        this.stage.add(this.layers.rectangle.borderLine);

        this.shapes.circle.main.on('dragmove', () => {
            this.shapes.circle.intersection.x(this.shapes.circle.main.x());
            this.shapes.circle.intersection.y(this.shapes.circle.main.y());
        });

        this.shapes.circle.intersection.on('dragmove', () => {
            this.shapes.circle.main.x(this.shapes.circle.intersection.x());
            this.shapes.circle.main.y(this.shapes.circle.intersection.y());
        });

        this.shapes.rectangle.main.on('dragmove', () => {
            this.shapes.rectangle.intersection.x(this.shapes.rectangle.main.x());
            this.shapes.rectangle.intersection.y(this.shapes.rectangle.main.y());
        });

        this.shapes.rectangle.intersection.on('dragmove', () => {
            this.shapes.rectangle.main.x(this.shapes.rectangle.intersection.x());
            this.shapes.rectangle.main.y(this.shapes.rectangle.intersection.y());
        });

        this.shapes.rectangle.borderBox.on('dragmove', () => {
            this.shapes.rectangle.borderLine.x(this.shapes.rectangle.borderBox.x());
            this.shapes.rectangle.borderLine.y(this.shapes.rectangle.borderBox.y());
        });

        this.stage.on('dragmove', () => {
            this.clip();
            this.draw();
        });

        this.angle = 0;

        this.animations = {};
        this.animations.rotation = new Konva.Animation(() => {
            if (this.angle >= 360) {
                this.angle = 0;
            }

            this.shapes.rectangle.main.rotation(this.angle);
            this.shapes.rectangle.intersection.rotation(this.angle);

            this.shapes.circle.main.rotation(-this.angle);
            this.shapes.circle.intersection.rotation(-this.angle);


            this.angle += 0.3;
        }, this.stage);
    }

    draw() {
        this.stage.batchDraw();

        const mainRectangleTween = TweenLite.to(this.shapes.rectangle.main, 3, {
            paused: true,
        });
        const intersectionRectangleTween = TweenLite.to(this.shapes.rectangle.intersection, 3, {
            paused: true
        });
        const mainCircleTween = TweenLite.to(this.shapes.circle.main, 3, {
            paused: true
        });
        const intersectionCircleTween = TweenLite.to(this.shapes.circle.intersection, 3, {
            paused: true
        });


        document.getElementById('toggle_moving').addEventListener('click', () => {
            canvas.animations.rotation.start();
            const x = (this.shapes.circle.main.x() + this.shapes.rectangle.main.x()) / 2;
            const y = (this.shapes.circle.main.y() + this.shapes.rectangle.main.y()) / 2;

            if (this.shapes.circle.main.x() !== this.shapes.rectangle.main.x() && this.shapes.circle.main.y() !== this.shapes.circle.main.x()) {
                mainRectangleTween.vars.konva = {
                    x: x,
                    y: y,
                };
                intersectionRectangleTween.vars.konva = {
                    x: x,
                    y: y,
                };
                mainCircleTween.vars.konva = {
                    x: x,
                    y: y,
                };
                intersectionCircleTween.vars.konva = {
                    x: x,
                    y: y,
                };
                mainRectangleTween.play()
                intersectionRectangleTween.play();
                mainCircleTween.play();
                intersectionCircleTween.play();
            }
        });
    }

    initChangeOrderFn() {
        document.querySelector('#change_order').addEventListener('click', () => {
            this.isLeftOnTop = !this.isLeftOnTop;
            this.draw();
            this.combineElements();
        })
    }
}

let canvas;
const handleDOMContentLoaded = () => {
    canvas = new Canvas();
};

const rotate = false;

document.addEventListener('DOMContentLoaded', handleDOMContentLoaded);
