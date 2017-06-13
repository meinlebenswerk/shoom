
import {Buffer} from "buffer";

export interface ShmConstructorOpts {
  /**
   * A name for the shared memory object in the global OS namespace.
   * 
   * Something like `myapp-${pid}.shm` is okay. shoom will modify the name
   * to make it "valid" on the target OS. If other consumers of the shared memory
   * object are also using node-shoom (node.js), or shoom (C++), then the same
   * path will map to the same memory object.
   */
  path: string;

  /**
   * The size of the shared memory object, in bytes. When creating, this
   * sets the maximum size that can be mapped. When reading, specifying
   * a different size than what the object was created with is undefined behavior.
   * 
   * (Most probably: giving a larger size may fail to map, or fault when trying
   * to read out of bounds, giving a smaller size may work fine, you just won't be
   * able to read the end of the object since it won't be mapped.)
   */
  size: number;
}

export declare class Shm {
  /**
   * Sets values for an shm object that's about to be created or opened.
   * If you're expecting another process to open your SHM object, don't forget
   * to call `create()`.
   */
  constructor(opts: ShmConstructorOpts);

  /**
   * Asks the OS to create a shared memory object with the parameters given
   * to the constructor. If an existing shared memory object already exists
   * with the same path, it will be deleted.
   * 
   * Throws an exception if something goes wrong.
   * 
   * Things that may go wrong:
   *   - Permission to create shared memory objects denied
   *   - Existing memory object is locked somehow
   *   - Out of memory
   *   - Like, a hundred other things. It's an OS-level functionality, tons of
   *   it eventually breaks in funny ways.
   */
  create();

  /**
   * Asks the OS to open and map an existing shared memory object with the
   * parameters given to the constructor.
   * 
   * Throws an exception if it can't. 
   * 
   * Most notably, this will fail if no such shared memory object was created
   * previously, by another process.
   */
  open();

  /**
   * Write `source` at position `offset` into the shared memory object.
   * 
   * Note: shoom is fast, but it's not particularly safe. The onus to
   * check boundaries is on you. If you pass a buffer too big, you'll
   * be writing outside the boundaries of the mapped memory, and your OS
   * will hit you with its hammer of choice.
   */
  write(offset: number, source: Buffer);

  /**
   * Reads `destination.length` bytes from the shared memory object at
   * position `offset` and writes them into `destination.
   * 
   * Note: shoom is fast, but it's not particularly safe. The onus to
   * check boundaries is on you. If you pass a buffer too big, you'll
   * be reading outside the boundaries of the mapped memory, and your OS
   * will understandably be less than thrilled about it.
   */
  read(offset: number, destination: Buffer);
}
