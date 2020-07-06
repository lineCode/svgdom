#pragma once

#include "visitor.hpp"

namespace svgdom{

class stream_writer : virtual public const_visitor{
private:
	void childrenToStream(const container& e);
	
	std::string name;
	std::vector<std::pair<std::string, std::string>> attributes;
protected:
	// s, indent, and indentStr() are made protected to allow writing arbitrary content to stream for those who extend the class, as this was needed in some projects.
	std::ostream& s;
	unsigned indent = 0;
	std::string indent_str();
	
	void set_name(const std::string& name);
	void add_attribute(const std::string& name, const std::string& value);
	void add_attribute(const std::string& name, const length& value);
	void add_attribute(const std::string& name, real value);
	void write(const container* children = nullptr, const std::string& content = std::string());
	
	void add_element_attributes(const element& e);
	void add_transformable_attributes(const transformable& e);
	void add_styleable_attributes(const styleable& e);
	void add_view_boxed_attributes(const view_boxed& e);
	void add_aspect_ratioed_attributes(const aspect_ratioed& e);
	void add_rectangle_attributes(
			const rectangle& e,
			const rectangle& default_values = rectangle(
					length(0, length_unit::percent),
					length(0, length_unit::percent),
					length(100, length_unit::percent),
					length(100, length_unit::percent)
				)
		);
	void add_shape_attributes(const shape& e);
	void add_referencing_attributes(const referencing& e);
	void add_gradient_attributes(const gradient& e);
	void add_filter_primitive_attributes(const filter_primitive& e);
	void add_inputable_attributes(const inputable& e);
	void add_second_inputable_attributes(const second_inputable& e);
	void add_text_positioning_attributes(const text_positioning& e);
	
public:
	stream_writer(std::ostream& s) : s(s) {}
	
	void visit(const g_element& e) override;
	void visit(const svg_element& e) override;
	void visit(const symbol_element& e) override;
	void visit(const defs_element& e) override;
	void visit(const linear_gradient_element& e) override;
	void visit(const radial_gradient_element& e) override;
	void visit(const gradient::stop_element& e) override;
	void visit(const use_element& e) override;
	void visit(const path_element& e) override;
	void visit(const circle_element& e) override;
	void visit(const polyline_element& e) override;
	void visit(const polygon_element& e) override;
	void visit(const ellipse_element& e) override;
	void visit(const rect_element& e) override;
	void visit(const line_element& e) override;
	void visit(const filter_element& e) override;
	void visit(const fe_gaussian_blur_element& e) override;
	void visit(const fe_color_matrix_element& e) override;
	void visit(const FeBlendElement& e) override;
	void visit(const fe_composite_element& e) override;
	void visit(const image_element& e) override;
	void visit(const mask_element& e) override;
	void visit(const text_element& e) override;
	void visit(const style_element& e) override;
};

}
