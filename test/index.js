const test = require("tape");
const shoom = require("..");

test("can create, open, write and read to shared memory", function (t) {
    const server = new shoom.Shm({path: "shoom_test", size: 4});
    server.create();
    server.write(0, new Buffer([1, 2, 3, 4]));

    const client = new shoom.Shm({path: "shoom_test", size: 4});
    client.open();
    const b = new Buffer(4);
    client.read(0, b);

    t.equal(b[0], 1);
    t.equal(b[1], 2);
    t.equal(b[2], 3);
    t.equal(b[3], 4);

    t.end();
})

test("cannot open non-existent shared memory", function (t) {
    const client = new shoom.Shm({path: "shoom_woops", size: 4});
    t.throws(function () {
        client.open()
    }, /Could not open/);
    t.end();
})
