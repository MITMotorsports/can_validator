I just finished up a little tool that will hopefully be useful managing traffic on the vehicle's CAN bus. Sometime on Saturday or otherwise, add the specs for the CAN messages that your module needs to use here.

The format should be pretty self explanatory (but feel free to ask questions). Then run:

./check.py --validate_spec id_specification.txt

to make sure than the changes you made are A+, consistent, and valid*. Down the road, we can run MiniMon to listen over UART and produce a CSV log of all CAN messages on the bus.

./check.py --check_log id_specification.txt FirstLogCAN.CSV

will validate the spec, produce a summarized log output, and check that what we see in the log matches the spec-defined bus behavior. Code and examples found here.

---------------------------

* What is actually being checked when you 'validate' the spec? A few things:

- Messages don't have repeated symbolic names or conflicting IDs
- Defined data fields do not overlap and fit within the CAN frame data field
- Data field values and symbols are 1:1 (one data value doesn't map to two symbols)
- Specified CAN ID fits within the CAN frame data field
- And a few other sanitary things

** What is actually being done/checked/produced when I compare the log against the defined spec?

- Frequency constraints are met (e.g. is the heartbeat being sent out atleast every 1 second?)
- Consecutive, repeated messages are compressed into 'message blocks' with start and end times. This dramatically improves readability of the log
- IDs and data fields are converted to their human-readable symbols (as defined in the spec!)