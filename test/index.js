const test = require("tape");
const shoom = require("..");

test("can create, open, write and read to shared memory", function (t) {
    const server = new shoom.Shm({path: "shoom_test", size: 4});
    server.create();
    server.write(0, Buffer.from([1, 2, 3, 4]));

    const client = new shoom.Shm({path: "shoom_test", size: 4});
    client.open();
    const b = Buffer.alloc(4);
    client.read(0, b);

    t.equal(b[0], 1);
    t.equal(b[1], 2);
    t.equal(b[2], 3);
    t.equal(b[3], 4);

    t.end();
})

test("buffer works in cyclic-read-mode", function (t) {
    const server = new shoom.Shm({path: "shoom_test", size: 4});
    server.create();
    server.write(0, Buffer.from([1, 2, 3, 4]));

    const client = new shoom.Shm({path: "shoom_test", size: 4});
    client.open();
    const b = Buffer.alloc(4);
    client.readCyclic(2, b);

    t.equal(b[0], 3);
    t.equal(b[1], 4);
    t.equal(b[2], 1);
    t.equal(b[3], 2);

    t.end();
})

test("buffer works in cyclic-write-mode", function (t) {
    const server = new shoom.Shm({path: "shoom_test", size: 4});
    server.create();
    server.write(2, Buffer.from([1, 2, 3, 4]));

    const client = new shoom.Shm({path: "shoom_test", size: 4});
    client.open();
    const b = Buffer.alloc(4);
    client.readCyclic(0, b);

    t.equal(b[0], 3);
    t.equal(b[1], 4);
    t.equal(b[2], 1);
    t.equal(b[3], 2);

    t.end();
})


test("cannot open non-existent shared memory", function (t) {
    const client = new shoom.Shm({path: "shoom_woops", size: 4});
    t.throws(function () {
        client.open()
    }, /Could not open/);
    t.end();
})
