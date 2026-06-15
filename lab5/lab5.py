import streamlit as st
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
import glob
import os

st.set_page_config(page_title="Лабораторна 5", layout="wide")
st.title("Аналіз вегетаційних індексів")

@st.cache_data
def load_data():
    files = glob.glob("vhi_id_*.csv")
    files.sort()
    all_data = {}
    for f in files:
        df = pd.read_csv(f, header=None, skiprows=2, usecols=[0, 1, 2, 3, 4, 5, 6],
                         names=['year', 'week', 'SMN', 'SMT', 'VCI', 'TCI', 'VHI'])
        df['year'] = df['year'].astype(str).str.replace(r'<[^>]*>', '', regex=True).str.strip()
        df['year'] = pd.to_numeric(df['year'], errors='coerce')
        df['week'] = pd.to_numeric(df['week'], errors='coerce')
        df = df.dropna(subset=['year', 'week'])
        
        df['year'] = df['year'].astype(int)
        df['week'] = df['week'].astype(int)
        
        all_data[f] = df
    return all_data, files

all_data, files = load_data()

if not files:
    st.error("Файли не знайдені! Переконайтесь, що CSV-файли лежать у папці з додатком.")
    st.stop()

if 'reset' not in st.session_state:
    st.session_state.reset = False

def reset_filters():
    st.session_state.reset = True

if st.session_state.reset:
    st.session_state.metric = "VHI"
    st.session_state.selected_file = files[0]
    st.session_state.week_range = (1, 52)
    st.session_state.year_range = (1982, 2024)
    st.session_state.sort_asc = False
    st.session_state.sort_desc = False
    st.session_state.reset = False

st.sidebar.header("Параметри фільтрації")

metric = st.sidebar.selectbox("Оберіть показник:", ["VCI", "TCI", "VHI"], key="metric")
selected_file = st.sidebar.selectbox("Оберіть файл області:", files, key="selected_file")

df = all_data[selected_file]
min_year, max_year = int(df['year'].min()), int(df['year'].max())

week_range = st.sidebar.slider("Інтервал тижнів:", 1, 52, (1, 52), key="week_range")
year_range = st.sidebar.slider("Інтервал років:", min_year, max_year, (min_year, max_year), key="year_range")

sort_asc = st.sidebar.checkbox("Сортувати за зростанням", key="sort_asc")
sort_desc = st.sidebar.checkbox("Сортувати за спаданням", key="sort_desc")

st.sidebar.button("Reset (Скинути фільтри)", on_click=reset_filters)

if sort_asc and sort_desc:
    st.sidebar.warning("Увімкнено обидва сортування! Дані відображатимуться без сортування.")
    sort_mode = None
elif sort_asc:
    sort_mode = "asc"
elif sort_desc:
    sort_mode = "desc"
else:
    sort_mode = None

filtered_df = df[(df['year'] >= year_range[0]) & (df['year'] <= year_range[1]) &
                 (df['week'] >= week_range[0]) & (df['week'] <= week_range[1])]

if sort_mode == "asc":
    filtered_df = filtered_df.sort_values(by=metric, ascending=True)
elif sort_mode == "desc":
    filtered_df = filtered_df.sort_values(by=metric, ascending=False)
tab1, tab2, tab3 = st.tabs(["Таблиця даних", "Графік показника", "Порівняння областей"])

with tab1:
    st.subheader(f"Дані для обраної області ({metric})")
    st.dataframe(filtered_df)

with tab2:
    st.subheader(f"Динаміка {metric} (Роки: {year_range[0]}-{year_range[1]}, Тижні: {week_range[0]}-{week_range[1]})")
    if not filtered_df.empty:
        fig, ax = plt.subplots(figsize=(10, 5))
        if sort_mode:
            plot_df = filtered_df.head(50) 
            sns.barplot(data=plot_df, x=plot_df.index, y=metric, ax=ax, color='skyblue')
            plt.xticks([]) 
            plt.xlabel("Відсортовані записи")
        else:
            time_series_df = filtered_df.copy()
            time_series_df['Time'] = time_series_df['year'].astype(str) + "-" + time_series_df['week'].astype(str)
            ax.plot(time_series_df['Time'], time_series_df[metric], color='coral')
            ax.set_xticks(ax.get_xticks()[::len(time_series_df)//10 + 1]) 
            plt.xticks(rotation=45)
            
        plt.ylabel(metric)
        plt.grid(True, linestyle='--', alpha=0.7)
        st.pyplot(fig)
    else:
        st.write("Немає даних для відображення.")

with tab3:
    st.subheader(f"Середній {metric} по всіх областях за обраний період")
    
    compare_data = []
    for f_name, d in all_data.items():
        temp_df = d[(d['year'] >= year_range[0]) & (d['year'] <= year_range[1]) &
                    (d['week'] >= week_range[0]) & (d['week'] <= week_range[1])]
        
        try:
            prov_id = os.path.basename(f_name).split('_')[2]
        except:
            prov_id = f_name
            
        mean_val = temp_df[metric].mean()
        compare_data.append({"Область": prov_id, metric: mean_val})
        
    compare_df = pd.DataFrame(compare_data).dropna()
    
    if not compare_df.empty:
        fig2, ax2 = plt.subplots(figsize=(12, 6))
        sns.barplot(data=compare_df, x="Область", y=metric, ax=ax2, palette="viridis")
        plt.xticks(rotation=90)
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        st.pyplot(fig2)
    else:
        st.write("Немає даних для побудови порівняльного графіка.")