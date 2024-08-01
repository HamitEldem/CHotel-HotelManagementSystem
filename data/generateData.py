import pandas as pd
import random
import faker
from datetime import datetime, timedelta

fake = faker.Faker('tr_TR')

# Helper function to generate passwords
def generate_password(personnel_id):
    return str(int(personnel_id) * 2 + 5)

# Generate personnel data
departments = ["accounting", "front office", "housekeeping", "kitchen", "purchasing", "management", "sales"]
personnel_data = []

# General Manager
personnel_data.append({
    "personnel_id": "00000",
    "name": fake.first_name(),
    "surname": fake.last_name(),
    "department_no": "0",
    "worker_type": "general manager",
    "password": generate_password("00000")
})

# Department Managers and Workers
for i in range(1, 8):
    for j in range(1, 3):
        personnel_id = f"{i}{j}000"
        personnel_data.append({
            "personnel_id": personnel_id,
            "name": fake.first_name(),
            "surname": fake.last_name(),
            "department_no": str(i),
            "worker_type": "department manager" if j == 1 else "worker",
            "password": generate_password(personnel_id)
        })
        for k in range(1, 13):
            personnel_id = f"{i}{j}{str(k).zfill(3)}"
            personnel_data.append({
                "personnel_id": personnel_id,
                "name": fake.first_name(),
                "surname": fake.last_name(),
                "department_no": str(i),
                "worker_type": "worker",
                "password": generate_password(personnel_id)
            })

personnel_df = pd.DataFrame(personnel_data)
personnel_df.to_csv("personnel.csv", index=False)

# Generate rooms data
rooms_data = []
for floor in range(1, 6):
    for room in range(20):
        room_number = f"{floor}{str(room).zfill(2)}"
        occupied = random.choice([True, False])
        if occupied:
            days_to_empty = random.randint(1, 30)
            empty_date = (datetime.now() + timedelta(days=days_to_empty)).strftime('%Y-%m-%d')
        else:
            empty_date = None
        clean_status = random.choice(["clean", "dirty"])
        housekeeper_id = random.choice(personnel_df[personnel_df['department_no'] == "3"]['personnel_id'].values)
        rooms_data.append({
            "room_number": room_number,
            "occupied": occupied,
            "empty_date": empty_date,
            "clean_status": clean_status,
            "housekeeper_id": housekeeper_id
        })

rooms_df = pd.DataFrame(rooms_data)
rooms_df.to_csv("rooms.csv", index=False)

# Generate menu data
menu_data = []
for day in range(1, 31):
    for menu_type in ["breakfast", "lunch", "dinner"]:
        menu_data.append({
            "day": day,
            "menu_type": menu_type,
            "menu": fake.sentence(nb_words=5)
        })

menu_df = pd.DataFrame(menu_data)
menu_df.to_csv("menu.csv", index=False)

# Generate purchasing queue data
purchasing_queue_data = [{"item_id": i, "count": random.randint(1, 100)} for i in range(1, 101)]
purchasing_queue_df = pd.DataFrame(purchasing_queue_data)
purchasing_queue_df.to_csv("purchasing_queue.csv", index=False)

# Generate warehouse data
warehouse_data = [{"item_id": i, "count": random.randint(1, 200), "name": fake.word()} for i in range(1, 51)]
warehouse_df = pd.DataFrame(warehouse_data)
warehouse_df.to_csv("warehouse.csv", index=False)

# Generate accounting data
accounting_data = [{"account_id": i, "description": fake.sentence(), "amount": random.uniform(-1000, 1000), "date": fake.date()} for i in range(1, 101)]
accounting_df = pd.DataFrame(accounting_data)
accounting_df.to_csv("accounting.csv", index=False)

print("CSV files generated successfully.")

