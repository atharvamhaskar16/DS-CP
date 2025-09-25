📍 Project Roadmap – Smart EV Charging Allocation System
________________________________________
Phase 1: Planning & Requirements (Week 1)
•	✅ Define the problem statement and solution approach (done).
•	✅ Finalize the data structures to be used: Queue, Priority Queue, Hash Table, Tree, Set, Stack.
•	Decide on programming language (C for core logic, plus optional web frontend with JS/Python backend).
•	Sketch a simple system architecture diagram.
________________________________________
Phase 2: Backend Core Logic (Week 2–3)
🎯 Implement Data Structures in C
1.	Struct for EV
2.	Queue (Linked List) → Stores arriving EVs.
3.	3.Priority Queue (Heap) → Selects EV with highest priority.
4.	Hash Table → Stores EVs for fast lookup/update.
5.	Set → Tracks already charged EVs.
6.	Tree (BST) → Allows searching/filtering EVs.
7.	Stack → Stores previous states for undo/redo.
________________________________________
Phase 3: Core Algorithms (Week 3–4)
•	Function to calculate priority score.
•	Function to insert EV into queue + heap.
•	Function to allocate charging slot (pop from heap).
•	Function to update waiting time (timestamp-based).
•	Function to remove completed EV and store in Set.
•	Undo/Redo mechanism with Stack.
•	Filtering with Tree.
________________________________________
Phase 4: Simulation & Testing (Week 4–5)
•	Simulate EV arrivals with different:
o	Battery %
o	User types
o	Arrival times
•	Show allocations step by step.
•	Print logs:
•	EV3 (10% battery, Normal) → Allocated
•	EV1 (20% battery, Premium) → Allocated
•	EV2 (50% battery, Normal) → Waiting
•	Test edge cases: duplicate EVs, full queue, undo/redo.
________________________________________
Phase 5: Frontend Development (Week 5–6)
(If you want the full web frontend)
•	Frontend (HTML + CSS + JS / React)
o	Input form for EV ID, Battery %, User type.
o	Table for current queue.
o	Dashboard for priority list.
o	Charging slots view (3 slots visualized).
o	Buttons for Undo/Redo.
•	Backend (Python Flask / Node.js)
o	APIs:
	/addEV → Add new EV
	/getQueue → Get queue state
	/getPriorityList → Get priority list
	/allocate → Allocate charging slot
	/undo, /redo
•	Sync frontend with backend using JSON.
________________________________________
Phase 6: Integration & Demo (Week 6–7)
•	Connect C logic → APIs → Frontend.
•	Run simulation with live updates.
•	Prepare visual demo showing:
o	EV arrivals
o	Priority calculations
o	Charging slot allocation
________________________________________
Phase 7: Documentation & Presentation (Week 7)
•	Write project report:
o	Problem statement
o	Solution approach
o	Data structures used
o	Algorithm explanation
o	Simulation results
•	Create presentation slides with diagrams.
•	Prepare a demo run for evaluation.
________________________________________
✅ Final Deliverables
1.	C Program (Core Logic) – implements queue, heap, hash table, set, tree, stack.
2.	Simulation Logs – showing EV arrivals, priority updates, and allocations.
3.	Optional Web Frontend – interactive visualization.
4.	Documentation + Diagrams – for report and presentation.
5.	Demo Script – how to run and explain the project.

