
import pyrogue
import MyWrapper

class TestRoot(pyrogue.Root):
    def __init__(self):
        super().__init__(name="MyRoot")

        # Add master and slave devices
        self.add(MyWrapper.MyCustomMaster(name="testMaster"))
        self.add(MyWrapper.MyCustomSlave(name="testSlave"))

        # Connect master to slave
        self.testMaster >> self.testSlave

        # Start the tree
        #self.start()


with TestRoot() as r:
    # Set frame size to 200
    r.testMaster.FrameSize.set(200)

    # Generate 2 Frames
    r.testMaster.MyFrameGen()
    r.testMaster.MyFrameGen()

    # Display status
    print("Sent {} bytes in {} frames".format(r.testMaster.ByteCount.get(),r.testMaster.FrameCount.get()))
    print("Got  {} bytes in {} frames".format(r.testSlave.ByteCount.get(),r.testSlave.FrameCount.get()))

